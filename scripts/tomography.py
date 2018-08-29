

#################
## TO THE USER ##
#################

# To use the code to calculate tomography and to estimate error of a measurement, you can skip these tedious definations
# of functions and scroll down to the bottom of it, where marked as ##TESTING DATA##. You would find 5 input variables
# there. For the version 3.x of State_tomography.py, your mission is to find them out and type them in with a correct 
# format. The definations of these input variables could be find in the 'tutorial for tomography.pdf' which can be find 
# on the website, demo interface page. 
#
# Input variables names: 'tomo_input'(2-d array),'intensity'(1-d array),'conf'(dictionary), 'err_n'(int),
# 'err_functions'(string array).
#
# Bell state calulatuion is scanning 4 dimensions 


######################
## TO THE DEVELOPER ##
######################

# Everything in this code is based on the Matlab files you can download on our tomography website, a more detailed 
# comments and definations of variables could be found in those m files, I kept the function names as same as possible, 
# I have marked the modifications I did with comment in this code. It may has some parts that I didn't check with real
# data, I have mark them too. 
#
# 'UseDerivatives' is not working in this version, my guess is to use 'col_deriv=useder' commend in the optimization function
# scipy.optimize.leastsq. But it does not work.
#
# 'CrossTalk' has not been checked by datas. For 1 detector, it seems that we didn't use that variable in calculation. For 2 
# detectors, I didn't check the whole function 'filter_data_2n' at all.

from time import clock
start = clock()
import scipy as sp
from scipy.optimize import leastsq
from numpy.core.defchararray import add
import numpy as np
from math import *
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D



##########################
## TOMOGRAPHY CALCULATE ##
##########################

def getfield_default(s,name,default):
    if name in s:
        val = s[name]
    else:
        val = default
    
    return val

def filter_data_n(raw_counts,intensities,conf):
    qudit_sizes = getfield_default(conf,'QuditSizes',[2,2])
    conf['StateDimension'] = np.prod(qudit_sizes)
    window = getfield_default(conf,'Window',0)
    n_singles = len(qudit_sizes)
    n_measurements = len(raw_counts)
    
    t = raw_counts[:,0]
    singles = raw_counts[:,np.arange(n_singles)+1]
    coinc = raw_counts[:,n_singles+1]
    measurements = raw_counts[:,np.arange(n_singles+2,len(raw_counts[0]))]
    
    acc = np.prod(singles,axis=1)*(window*1e-9/t)**(n_singles-1)
    
    #haven't checked from:
    ctalk = getfield_default(conf,'Crosstalk',[])
    if np.shape(np.shape(ctalk))[0]<3:
        crosstalk = ctalk
    else:
        for j in range(np.shape(ctalk)[2]):
            crosstalk[j] = ctalk[:,:,j]
    if ctalk==[]:
        big_crosstalk = [1,zeros(2**nbits-1)]
    else:
        big_crosstalk = np.inner(crosstalk,crosstalk)
    #big_crosstalk = big_crosstalk * np.inner(eff,ones(n_coinc))
    #to here.    
    
    M2 = np.zeros([n_measurements,np.prod(qudit_sizes)])
    M1 = np.zeros([np.prod(qudit_sizes),np.prod(qudit_sizes),n_measurements])
    M2 = M2+0j
    M1 = M1+0j
    for j in range(n_measurements):
        psi = 1
        offset = 0
        for k in range(n_singles):
            M_length = qudit_sizes[k]
            psi_k = measurements[j,np.arange(offset,offset+M_length)]
            psi = np.outer(psi,psi_k)
            offset = offset+M_length
        psi = np.array([psi[0][0],psi[0][1],psi[1][0],psi[1][1]])
        M2[j,:] = psi
        M1[:,:,j] = np.outer(psi.conj().transpose(),psi)
    
    return([coinc,M1,M2,acc,conf])

def multiloop_index(j,lengths):
    ind = np.zeros(len(lengths))
    for k in range(len(lengths)-1):
        sz = np.prod(lengths[np.arange(k+1,len(lengths))])
        ind[k] = np.fix(j/sz)+1
        j = j % sz
    ind[len(ind)-1] = j+1
    
    return ind

def tensor_product(A,B):
    a = np.ndim(A)
    b = np.ndim(B)
    if (a==2)&(b==2):
        [n11,n12] = np.shape(A)
        [n21,n22] = np.shape(B)
        jj = n11*n21
        kk = n12*n22
        rv = np.zeros([jj,kk])+0j
        for j in range(jj):
            for k in range(kk):
                rv[j,k] = A[np.floor(j/n21),np.floor(k/n22)]*B[j%n21,k%n22]        
    elif (a==2)&(b==1):
        [n11,n12] = np.shape(A)
        n21 = len(B)
        jj = n11*n21
        kk = n12
        rv = np.zeros([jj,kk])+0j
        for j in range(jj):
            for k in range(kk):
                rv[j,k] = A[np.floor(j/n21),k]*B[j%n21]
    elif (a==1)&(b==2):
        [n21,n22] = np.shape(B)
        n11 = len(A)
        jj = n11*n21
        kk = n22
        rv = np.zeros([jj,kk])+0j
        for j in range(jj):
            for k in range(kk):
                rv[j,k] = A[np.floor(j/n21)]*B[j%n21,k]        
    elif (a==1)&(b==1):
        n11 = len(A)
        n12 = len(B)
        jj = n11*n12
        rv = np.zeros(jj)+0j
        for j in range(jj):
            rv[j] = A[np.floor(j/n21)]*B[j%n21]  
    elif (a==0)|(b==0):
        rv = A*B
    
    return rv

def filter_data_2n(raw_counts,intensities,conf):
    #didn't check yet
    if not np.isscalar(intensities):
        conf['DoDriftCorrection'] = 'no'
    nbits = getfield_default(conf,'NQubits',2)
    do_drift_corr = getfield_default(conf,'DoDriftCorrection','yes')
    do_drift_corr = do_drift_corr is 'yes'
    
    conf['StateDimension'] = 2**nbits
    
    n_singles = 2*nbits
    n_coinc = 2**nbits
    
    t = raw_counts[:,0]
    singles = raw_counts[:,np.arange(n_singles)+1]
    coinc = raw_counts[:,np.arange(n_singles+1,n_singles+n_coinc+1)]
    settings = raw_counts[:,np.arange(n_singles+n_coinc+1,len(raw_counts[0]))]    
    
    acc = np.zeros(np.shape(coinc))
    
    window = getfield_default(conf,'Window',0)
    if not np.isscalar(window):
        if any(window)>0:
            for j in range(n_coinc):
                idx = multiloop_index(j,2*np.ones(nbits))
                idx = idx + np.arange(0,n_singles-1,2) - 1
                idx = idx.astype(int)
                acc[:,j] = np.prod(np.real(singles[:,idx]),axis=1) * (window[j]*1e-9/np.real(t))**(nbits-1)
    
    eff = getfield_default(conf,'Efficiency',1)
    
    if do_drift_corr:
        intensity_map = np.dot(np.eye(np.shape(raw_counts)[0]),np.ones(n_coinc))
        z = np.zeros(np.prod(np.shape(coinc)))
        conf['intensityMap'] = np.concatenate(z,intensity_map)
    
    ctalk = getfield_default(conf,'Crosstalk',[])
    if np.shape(np.shape(ctalk))[0]<3:
        crosstalk = ctalk
    else:
        for j in range(np.shape(ctalk)[2]):
            crosstalk[j] = ctalk[:,:,j]    
    
    if ctalk==[]:
        big_crosstalk = np.eye(2**nbits)
    else:
        big_crosstalk = crosstalk[:]
        #was a tensor product, it does just same thing.

    big_crosstalk = big_crosstalk * np.outer(eff,np.ones(n_coinc))
    
    M = np.zeros([2**nbits,2**nbits,np.prod(np.shape(coinc))])+0j
    M2 = np.zeros([np.prod(np.shape(coinc)),2**nbits])+0j
    for j in range(np.shape(coinc)[0]):
        M_twiddle = np.zeros([2**nbits,2*2,2*2])+0j
        U = 1
        for k in range(nbits):
            alpha = settings[j][2*k]
            beta = settings[j][2*k+1]

            psi_k = np.array([alpha,beta])
            psip_k = np.array([np.conj(beta),np.conj(-alpha)])
            U_k = np.outer((np.array([1,0])),psi_k) + np.outer((np.array([0,1])),psip_k)
            U = tensor_product(U,U_k)
        for k in range(2**nbits):
            M_twiddle[k,:,:] = np.outer(U[:,k],U[:,k].conj().transpose())
            M2[j*n_coinc+k,:] = U[:,k].conj().transpose()
        for k in range(2**nbits):
            for l in range(2**nbits):
                M[:,:,j*(2**nbits)+k] = M[:,:,j*(2**nbits)+k] + M_twiddle[l,:,:]*big_crosstalk[k,l]
    M1 = M


    data = coinc.reshape((np.prod(np.shape(coinc)),1))
    acc = acc.reshape((np.prod(np.shape(acc)),1))
    return [data,M1,M2,acc,conf]

def sigma_N(j,N):
    if j<0 or j>N**2-1:
        print 'sigma_N: j out of range for SU(N)'
    
    m = np.int(np.fix(j/N))
    n = np.int(j%N)
    tmp1 = np.zeros([N,1])
    tmp2 = np.zeros([N,1])
    tmp1[m] = 1
    tmp2[n] = 1
    
    if m<n:
        matrix = (np.outer(tmp1,tmp2.conj().transpose())+np.outer(tmp2,tmp1.conj().transpose()))*np.sqrt(N/2.0)
    elif m>n:
        matrix = 1j*(np.outer(tmp1,tmp2.conj().transpose())-np.outer(tmp2,tmp1.conj().transpose()))*np.sqrt(N/2.0)
    elif (m+1)<N:
        z=np.zeros(N)
        for i in range(m+1):
            z[i] = 1
        matrix = -(np.sqrt(N/((m+1.0)**2+m+1.0)))*np.diag(z)
        matrix[m+1,m+1] = (m+1.0)*(np.sqrt(N/((m+1.0)**2+m+1.0)))
    else: #n=m=N
        matrix = np.matrix(np.identity(N))
    
    return matrix

def rho2stokes(rho):
    if rho.ndim==1:
        rho = np.outer(rho,rho.conj().transpose())
    
    d = len(rho)
    N = d**2
    
    S = np.zeros([N,1])+0j
    for j in range(N):
        S[j] = np.trace(np.inner(rho,sigma_N(j,d)))
        
    return S

def independent_set(measurements):
    m = measurements[0,:].conj().transpose()
    matrix = rho2stokes(np.outer(m,measurements[0,:]))
    max_rank = np.shape(matrix)[0]
    
    if (np.shape(measurements)[0]) == max_rank:
        s = np.ones([np.shape(measurements)[0],1])
        return s
    
    s = np.zeros([np.shape(measurements)[0],1])
    s[0] = 1
    cur_rank = 1
    
    for j in np.arange(1,np.shape(measurements)[0],1):
        m = measurements[j,:].conj().transpose()
        sv = rho2stokes(np.outer(m,measurements[j,:]))
        if (np.linalg.matrix_rank(np.concatenate((matrix,sv),axis=1),tol=0.001)) > cur_rank:
            matrix = np.concatenate((matrix,sv),axis=1)
            cur_rank = cur_rank + 1
            s[j] = 1
        else:
            s[j] = 0
        if cur_rank == max_rank:
            break
        
    return s

def B_matrix(projectors):
    dim_m = np.shape(projectors)[1]
    dim_b = dim_m**2
    tmp = np.zeros([dim_b,dim_b])+0j
    for i in range(dim_b):
        for j in range(dim_b):
            tmp[i][j] = np.inner(projectors[i],np.inner(sigma_N(j,dim_m),projectors[i].conj().transpose()))
    b = tmp.transpose()
    
    return b

def M_matrix(mu,projectors,B,B_inv):
    dim_m = np.shape(projectors)[1]
    dim_b = dim_m**2 
    
    tmp = np.zeros([dim_m,dim_m])
    for j in range(dim_b):
        tmp = tmp + B_inv[mu][j]*sigma_N(j,dim_m)
    m = tmp
    
    return m
    
def linear_tomography(data,measurements,m_set=()):
    if m_set == ():
        m_set = independent_set(measurements)
    if np.isscalar(m_set):
        n = len(data)
        linear_measurements = measurements
        linear_data = data
    
    else:
        n = np.int(np.sum(m_set))
        linear_measurements = measurements[(np.rot90(m_set==1.0)[0])]
        linear_data = data[(np.rot90(m_set==1.0)[0])]
    
    linear_rho = np.zeros([np.shape(measurements)[1],np.shape(measurements)[1]])
    
    B = B_matrix(linear_measurements)
    B_inv = np.linalg.inv(B)
    
    M = np.zeros([np.shape(measurements)[1],np.shape(measurements)[1],n]) + 0j
    for j in range(n):
        M[:,:,j] = M_matrix(j,linear_measurements,B,B_inv)
        linear_rho = linear_rho + linear_data[j]*M[:,:,j]
    
    intensity = np.trace(linear_rho)
    rho = linear_rho/intensity
    
    return [rho,intensity]

def make_positive(rho_in):
    D,V = np.linalg.eig(rho_in)
    rho = np.zeros(np.shape(rho_in))
    for j in range(len(D)):
        rho = rho + np.abs(D[j])*np.outer(V[:,j],V[:,j].conj().transpose())
    rho = (rho + rho.conj().transpose())/2.0
    
    return rho

def density2tm(rho):
    d = np.shape(rho)[0]
    if d == 1:
        tm = np.real(np.sqrt(rho))
        return tm
    
    tm = np.zeros(np.shape(rho))+0j
    last_element = rho[d-1][d-1]
    tm[d-1][d-1] = np.real(np.sqrt(last_element))
    if last_element > 0:
        temp = rho[d-1][range(d-1)]
        tm[d-1][range(d-1)] = temp/np.sqrt(last_element)
        recurse = np.hsplit(rho[range(d-1)],[d-1,d])[0] - np.outer(temp.conj().transpose(),temp)/last_element
    else:
        tm[d-1][range(d-1)] = np.zeros(d)
        recurse = np.hsplit(rho[range(d-1)],[d-1,d])[0]
    for i in range(d-1):
        tm[i][range(d-1)] = density2tm(recurse)[i][range(d-1)]
        
    return tm   
    
def density2t(rho):
    tm = density2tm(rho)
    d = len(tm)
    
    idx = 0
    cur_length = d
    t = np.zeros(d**2)
    
    for j in range(d):
        t[np.arange(idx,idx+cur_length)] = np.real(np.diag(tm,-j))
        idx = idx + cur_length
        if j>0:
            t[np.arange(idx,idx+cur_length)] = np.imag(np.diag(tm,-j))
            idx = idx + cur_length
        cur_length = cur_length -1
        
    return t

def one_in(idx,length):
    val = np.zeros(length)
    val[idx] = 1
    
    return val

def t_matrix(t):
    d = np.int(np.sqrt(len(t)))
    
    idx = 0
    cur_length = d
    tm = np.zeros([d,d])
    
    for j in range(np.int(d)):
        tm = tm + 1*np.diag(t[np.arange(idx,idx+cur_length)],-j)
        idx = idx + cur_length
        
        if j>0:
            tm = tm + 1j*np.diag(t[np.arange(idx,idx+cur_length)],-j)
            idx = idx + cur_length
        
        cur_length = cur_length - 1
        
    return tm

def t_to_density(t):
    tm = t_matrix(t)
    rho = np.dot(tm.conj().transpose(),tm)
    return rho

def initialize_fitness_global(M):
    num_t = np.shape(M)[0]**2
    num_M = np.shape(M)[2]
    M_size = np.shape(M)[0]
    
    tm = np.zeros([num_t,4,4])+0j
    
    for j in range(num_t):
        tm[j] = t_matrix(one_in(j,num_t))
    
    A = np.zeros([num_M,num_t,4,4])+0j
    B = A
    for j in range(num_M):
        for k in range(num_t):
            #Should use a sparse matrix here to make it easy.
            A[j][k] = np.dot(M[:,:,j],tm[k].conj().transpose())
            B[j][k] = np.dot(tm[k],M[:,:,j])
            
    return [A,B]

def maxlike_fitness(t,data,accidentals,M,conf,A,B):
    addone = getfield_default(conf,'AddOneCount',1)
    useder = getfield_default(conf,'UseDerivative',1)
    #this is not good
    intmap = getfield_default(conf,'IntensityMap',[[1]])
    sz = getfield_default(conf,'StateDimention',0)
    n_data = np.shape(data)[0]
    
    if type(addone) is str:
            addone = addone is 'yes'     
    if type(useder) is str:
        useder = useder is 'yes'
    n_int = np.shape(intmap)[1] - 1
    if sz>0:
        nt = sz**2
    else:
        nt = len(t) - n_int
        sz = np.sqrt(nt)
    
    tm = t_matrix(t[range(nt)])
    rho = np.dot(tm.conj().transpose(),tm)
    
    #I ignore something here using nargin and nargout, it's difficult in python, seems like A and B checkpoint, still have the sparse problem
    
    if n_int > 0: 
        rel_intensity = np.dot(intmap,[1,t[nt:len(t)]])
        #didn't check
    else:
        rel_intensity = np.ones(np.shape(M)[2])
    
    prediction = np.zeros(np.shape(M)[2])+0j
    
    for j in range(len(prediction)):
        prediction[j] = rel_intensity[j]*np.real(np.trace(np.dot(M[:,:,j],rho))) + accidentals[j]
        prediction[j] = np.max(prediction[j],0.01)
    
    val = (prediction - data)/np.sqrt(prediction)
    val = np.float64(np.real(val))
    return val

def maxlike_fitness2(t,data,accidentals,M,conf,A,B):
    addone = getfield_default(conf,'AddOneCount',1)
    useder = getfield_default(conf,'UseDerivatives',1)
    #this is not good
    intmap = getfield_default(conf,'IntensityMap',[[1]])
    sz = getfield_default(conf,'StateDimention',0)
    n_data = np.shape(data)[0]
    
    if type(addone) is str:
            addone = addone is 'yes'     
    if type(useder) is str:
        useder = useder is 'yes'
    n_int = np.shape(intmap)[1] - 1
    if sz>0:
        nt = sz**2
    else:
        nt = len(t) - n_int
        sz = np.sqrt(nt)
    
    tm = t_matrix(t[range(nt)])
    rho = np.dot(tm.conj().transpose(),tm)
    
    #I ignore something here using nargin and nargout, kinda difficult in python, seems like A and B checkpoint
    
    if n_int > 0: 
        rel_intensity = np.dot(intmap,[1,t[nt:len(t)]])
        #didn't check
    else:
        rel_intensity = np.ones(np.shape(M)[2])
    
    prediction = np.zeros(np.shape(M)[2])+0j
    
    for j in range(len(prediction)):
        prediction[j] = rel_intensity[j]*np.real(np.trace(np.dot(M[:,:,j],rho))) + accidentals[j]
        prediction[j] = np.max(prediction[j],0.01)
    
    jacob = 0
    if useder:
        jacob1 = np.zeros([len(data),nt])+0j
        for j in range(len(data)):
            for k in range(nt):
                #I don't know how the .conj().transpose() of A[j][k] come from, but I have to correct it like that.
                tmp = np.dot(A[j][k].conj().transpose(),tm) + np.dot(tm.conj().transpose(),B[j][k])
                jacob1[j][k] = rel_intensity[j]*np.trace(tmp)/np.sqrt(prediction[j])
                jacob1[j][k] = jacob1[j][k]*(1-0.5+0.5*data[j]/prediction[j])
        
        if n_int>0:
            #didn't check 
            tmp1 = ((prediction-accidentals)/np.sqrt(prediction))*(1-0.5+0.5*data/prediction)
            tmp2 = np.outer(tmp1,1/t[np.arange(nt,len(t))].transpose())
            jacob2 = np.dot(intmap,np.vstack((np.zeros(10),np.identity(10))))*tmp2
            jacob = np.hstack((jacob1,jacob2))
        else:
            jacob = jacob1
    jacob = np.float64(np.real(jacob))
    
    return jacob    

def maximum_likelihood_tomography(rho0,data,M,acc,conf):
    rho0 = make_positive(rho0)
    rho0 = rho0/(np.trace(rho0))
    init_intensity = np.mean(data) * np.shape(rho0)[0]
    t0 = density2t(rho0)
    n_t = len(t0)
    
    #t_to_density(t0)
    t0 = t0+0.0001
    t0 = t0 * np.sqrt(init_intensity)
    
    #this [[1]] is not good
    intmap = getfield_default(conf,'IntensityMap',[[1]])
    n_int = np.shape(intmap)[1]-1
    t0 = np.concatenate((t0,np.ones(n_int)),axis=0)
    
    #options
    useder = getfield_default(conf,'UseDerivative',1)
    
    if type(useder) is str:
        useder = useder is 'yes'
        
    #Should use a sparse matrix here to make it easy.
    [A,B] = initialize_fitness_global(M)
    
    tmp = maxlike_fitness(t0,data,acc,M,conf,A,B)
    data = np.real(data)
    if useder:
        [t,cov_x] = leastsq(maxlike_fitness,np.real(t0),args=(data,acc,M,conf,A,B),Dfun=maxlike_fitness2)
    else:
        [t,cov_x] = leastsq(maxlike_fitness,np.real(t0),args=(data,acc,M,conf,A,B))
    fval = np.sum(maxlike_fitness(t,data,acc,M,conf,A,B)**2)
    
    base_intensity = np.sum((t[range(n_t)])**2)
    #t_matrix(t[range(n_t)])
    matrix = t_to_density(t[range(n_t)])
    intensity = np.trace(matrix)
    rho = matrix/intensity
    intensity = np.float64(np.real(intensity))
    
    return [rho,intensity,fval]

def state_tomography(raw_counts,intensities,conf):
    rho0 = getfield_default(conf,'RhoStart',[])
    ndet = conf['NDetectors']

    if (ndet==2):
        [data,M1,M2,acc,conf] = filter_data_2n(raw_counts,intensities,conf)
        #2ndet still need to check with data
    else:
        [data,M1,M2,acc,conf] = filter_data_n(raw_counts,intensities,conf)
        
    if not rho0:
        [rho0,intensity0] = linear_tomography(data,M2)
    [rho,intensity,fval] = maximum_likelihood_tomography(rho0,data,M1,acc,conf)

    return [rho,intensity,fval]


####################
## ERROR ESTIMATE ##
####################


def fidelity(state1,state2):
    pure = 0
    if len(np.shape(state1))==1:
        rho1 = np.dot(state1,state1.conj().transpose())
        pure = 1
    elif np.shape(state1)[1] == np.shape(state1)[0]:
        rho1 = state1
    else:
        print("State1 is not a vector or density matrix")
        
    if len(np.shape(state2))==1:
        rho2 = np.dot(state2,state2.conj().transpose())
        pure = 1
    elif np.shape(state2)[1] == np.shape(state2)[0]:
        rho2 = state2
    else:
        print("State1 is not a vector or density matrix")  
    
    rho1 = rho1 / np.trace(rho1)
    rho2 = rho2 / np.trace(rho2)
    
    rho1 = (rho1+rho1.conj().transpose())/2
    
    
    if pure:
        val = np.trace(np.dot(rho1,rho2))
    else:
        tmp = sp.linalg.sqrtm(rho1)
        a = np.dot(tmp,np.dot(rho2,tmp))
        ev = np.linalg.eig(a)[0]
        val = np.sum(ev**(0.5))**2
    val = np.real(val)
    
    return val

def concurrence(rho):
    if min(np.shape(rho))==1:
        rho = np.dot(rho,rho.conj().transpose())
        #psi??, I think there something wrong here in m files.
    
    Z = np.array([[0,0,0,-1],[0,0,1,0],[0,1,0,0],[-1,0,0,0]])
    R = np.dot(rho,np.dot(Z,np.dot(rho.conj(),Z)))
    [r,right] = np.linalg.eig(R)
    #left = np.linalg.inv(right)
    r = np.real(r)
    
    tmp = np.sort(np.sqrt(r+0j))
    C = np.real(tmp[3]-tmp[2]-tmp[1]-tmp[0])
    C = np.max([C,0])
    
    return C

def tangle(rho):
    C = concurrence(rho)
    T = C**2
    
    return T

def entanglement(rho):
    t = tangle(rho)
    x = (1 + np.sqrt(1-t))/2
    if x == 0:
        E = 0
    elif x == 1:
        E = 1
    else:
        E = -x*np.log2(x) - (1-x)*np.log2(1-x)
    
    return E

def entropy(rho):
    [D,ignore] = np.linalg.eig(rho)
    E = np.real(D)
    S = 0
    for a in range(len(E)):
        if E[a] > 0:
            S = S - E[a]*np.log2(E[a])
    
    return S

def linear_entropy(rho):
    if min(np.shape(rho)) == 1:
        lin_e = 0
    else:
        d = len(rho)
        lin_e = d * np.real(1-np.trace(np.dot(rho,rho)))/(d-1)
    
    return lin_e

def partial_transpose_first(M,d):
    if np.shape(M)[0] == d:
        val = M.tranpose()
    else:
        Na = np.int(d)
        Nb = np.int(len(M)/d)
        Y = np.zeros([Nb,Nb,Na,Na])+0j
        val = np.zeros([len(M),len(M)])+0j
        for j in range(Nb):
            for k in range(Nb):
                Y[j,k] = M[j*Nb:j*Nb+Na,k*Nb:k*Nb+Na]
        for j in range(Nb):
            for k in range(Nb):
                val[j*Nb:j*Nb+Na,k*Nb:k*Nb+Na] = Y[k,j]
        
        return val
        
def partial_transpose(rho,n,D=np.nan):
    if min(np.shape(rho)) == 1:
            rho = np.dot(rho,rho.conj().transpose())    
    
    if D is np.nan:
        n_qubit = np.log2(np.shape(rho)[0])
        if not n_qubit%1:
            D = 2 * np.ones(n_qubit)
        else:
            print 'dimension of rho is incorrect.'
    if n<0:
        Na = 1.0
        Nb = 1.0
        Nc = np.prod(D)
    elif n==0:
        Na = 1.0
        Nb = D[n]
        Nc = np.prod(D[np.arange(n+1,len(D))])
    elif (n>0)&(n<len(D)):
        Na = np.prod(D[range(n-1)])
        Nb = D[n]
        Nc = np.prod(D[np.arange(n+1,len(D))])
    elif n==len(D):
        Na = np.prod(D[range(n-1)])
        Nb = D[n]
        Nc = 1.0
    elif n>len(D):
        Na = np.prod(D)
        Nb = 1.0
        Nc = 1.0
    
    if Na==1:
        rv = partial_transpose_first(rho,Nb)
    # I did't check from here
    else:
        sub_sizes = Nb*Nc
        Y = np.zeros([sub_sizes,sub_sizes,Na,Na])+0j
        for j in range(sub_sizes):
            for k in range(sub_sizes):
                Y[j,k] = rho[j*sub_sizes:j*sub_sizes+Na,k*sub_sizes:k*sub_sizes+Na]
        
        rv = np.zeros([len(rho),len(rho)])+0j
                
        for j in range(Na):
            for k in range(Na):
                rv[j*Nb:j*Nb+Na,k*Nb:k*Nb+Na] = partial_transpose_first(Y[j,k],Nb)
                
    return rv    

def negativity(rho):
    if min(np.shape(rho)) == 1:
        rho = np.dot(rho,rho.conj().transpose())
    
    rho1 = partial_transpose(rho,0)
    val = -2*np.min(np.min(np.real(np.linalg.eig(rho1)[0])),0)
    
    return val

def trace_dist(rho1,rho2):
    #didn't checked, and would not be called in this version.
    s1 = rho2stokes(rho1)
    s2 = rho2stokes(rho2)
    s = s1 - s2
    val = np.sqrt(np.dot(s.conj().transpose(),s))/2
    
    return val

def fevel(funcName,*args):
    return eval(funcName)(*args)

def tomography_error(raw_data,intensities,ndet,errfunc,n=100):
    [rho0,i,f] = state_tomography(raw_data,intensities,ndet)
    
    n_fun = len(errfunc)
    data = np.zeros([n,n_fun])
    fid = np.zeros(n)
    
    for j in range(n):
        print 'The',j+1,'of',n,'time of error estimating'
        test_data = np.zeros([len(raw_data[:,0]),3])
        for k in [1,2,3]:
            for l in range(len(raw_data[:,0])):
                test_data[l,(k-1)] = np.random.poisson(np.real(raw_data[l,k]))
        test_data = np.concatenate((np.reshape(raw_data[:,0],(len(raw_data[:,0]),1)),test_data,raw_data[:,np.arange(4,len(raw_data[0,:]))]),axis=1)
        #I am not sure this poisson random method do the same thing with Matlab one.
        
        [rho,inten,f] = state_tomography(test_data,intensities,ndet)
        fid[j] = fidelity(rho0,rho)
        for k in range(n_fun):
            data[j,k] = fevel(errfunc[k],rho)
    
    errs = np.zeros(n_fun)
    means = np.zeros(n_fun)
    ##There is something wrong with m files, errs and means should be an array included n_fun elements.
    for k in range(n_fun):
        errs[k] = np.std(data[:,k])
        means[k] = np.mean(data[:,k])
    mean_fid = np.mean(fid)
    
    return [errs,means,mean_fid]



################
## Bell State ##
################

def coinmat(a,b):
    k = np.array([np.cos(a)*np.cos(b),np.cos(a)*np.sin(b),np.sin(a)*np.cos(b),np.sin(a)*np.sin(b)])
    cmat = np.outer(k,k)
    
    return cmat

def websiteBellsettings_range(rho,partsize,arange,brange,aprange,bprange):
    
    sval = 0
    aval = 0
    apval = 0
    bval = 0
    bpval = 0
    
    for a in np.linspace(arange[0],arange[1],partsize):
        for ap in np.linspace(aprange[0],aprange[1],partsize):
            for b in np.linspace(brange[0],brange[1],partsize):
                for bp in np.linspace(bprange[0],bprange[1],partsize):
                    npp = np.real(np.trace(np.dot(coinmat(a,b),rho)))
                    nmm = np.real(np.trace(np.dot(coinmat(a+np.pi/2,b+np.pi/2),rho)))
                    e_ab = 2*(npp+nmm)-1
                    
                    npp = np.real(np.trace(np.dot(coinmat(ap,b),rho)))
                    nmm = np.real(np.trace(np.dot(coinmat(ap+np.pi/2,b+np.pi/2),rho)))
                    e_apb = 2*(npp+nmm)-1
                    
                    npp = np.real(np.trace(np.dot(coinmat(a,bp),rho)))
                    nmm = np.real(np.trace(np.dot(coinmat(a+np.pi/2,bp+np.pi/2),rho)))
                    e_abp = 2*(npp+nmm)-1

                    npp = np.real(np.trace(np.dot(coinmat(ap,bp),rho)))
                    nmm = np.real(np.trace(np.dot(coinmat(ap+np.pi/2,bp+np.pi/2),rho)))
                    e_apbp = 2*(npp+nmm)-1     
                    
                    s = e_ab + e_abp + e_apb + e_apbp - 2*np.min([e_ab,e_abp,e_apb,e_apbp])
                    
                    if s>sval:
                        sval = s
                        aval = a
                        apval = ap
                        bval = b
                        bpval = bp
    
    arange_s = [np.max([aval-((arange[1]-arange[0])/partsize),0]),np.min([aval+((arange[1]-arange[0])/partsize),np.pi/2])]
    aprange_s = [np.max([apval-((aprange[1]-aprange[0])/partsize),0]),np.min([apval+((aprange[1]-aprange[0])/partsize),np.pi/2])]
    brange_s = [np.max([bval-((brange[1]-brange[0])/partsize),0]),np.min([bval+((brange[1]-brange[0])/partsize),np.pi/2])]
    bprange_s = [np.max([bpval-((bprange[1]-bprange[0])/partsize),0]),np.min([bpval+((bprange[1]-bprange[0])/partsize),np.pi/2])]
    
    
    return [sval,aval,apval,bval,bpval,arange_s,brange_s,aprange_s,bprange_s]

def websiteBellsettings_range_init(rho,partsize):
    sval = 0
    aval = 0
    apval = 0
    bval = 0
    bpval = 0
    
    for a in np.linspace(0,np.pi/2,partsize):
        for ap in np.linspace(a,np.pi/2,partsize):
            for b in np.linspace(0,np.pi/2,partsize):
                for bp in np.linspace(b,np.pi/2,partsize):
                    npp = np.real(np.trace(np.dot(coinmat(a,b),rho)))
                    nmm = np.real(np.trace(np.dot(coinmat(a+np.pi/2,b+np.pi/2),rho)))
                    e_ab = 2*(npp+nmm)-1
                    
                    npp = np.real(np.trace(np.dot(coinmat(ap,b),rho)))
                    nmm = np.real(np.trace(np.dot(coinmat(ap+np.pi/2,b+np.pi/2),rho)))
                    e_apb = 2*(npp+nmm)-1
                    
                    npp = np.real(np.trace(np.dot(coinmat(a,bp),rho)))
                    nmm = np.real(np.trace(np.dot(coinmat(a+np.pi/2,bp+np.pi/2),rho)))
                    e_abp = 2*(npp+nmm)-1

                    npp = np.real(np.trace(np.dot(coinmat(ap,bp),rho)))
                    nmm = np.real(np.trace(np.dot(coinmat(ap+np.pi/2,bp+np.pi/2),rho)))
                    e_apbp = 2*(npp+nmm)-1     
                    
                    s = e_ab + e_abp + e_apb + e_apbp - 2*np.min([e_ab,e_abp,e_apb,e_apbp])
                    
                    if s>sval:
                        sval = s
                        aval = a
                        apval = ap
                        bval = b
                        bpval = bp
    
    arange_s = [np.max([aval-((np.pi/2)/partsize),0]),np.min([aval+((np.pi/2)/partsize),np.pi/2])]
    aprange_s = [np.max([apval-((np.pi/2)/partsize),0]),np.min([apval+((np.pi/2)/partsize),np.pi/2])]
    brange_s = [np.max([bval-((np.pi/2)/partsize),0]),np.min([bval+((np.pi/2)/partsize),np.pi/2])]
    bprange_s = [np.max([bpval-((np.pi/2)/partsize),0]),np.min([bpval+((np.pi/2)/partsize),np.pi/2])]
    
    
    return [sval,arange_s,brange_s,aprange_s,bprange_s]    
                    
def websiteBellsettings(rho,partsize_init,partsize,times):
    
    [s,arange,brange,aprange,bprange] = websiteBellsettings_range_init(rho,partsize_init)
    
    for j in range(times):
        #print s
        [s,a,ap,b,bp,arange,brange,aprange,bprange] = websiteBellsettings_range(rho,partsize,arange,brange,aprange,bprange)
    
    return [s,a,ap,b,bp]
    


##################
## TESTING DATA ##
##################


tomo_input=np.array([[1,149252,155232,5671,1,0,1,0],[1,150002,153884,45,1,0,0,1],\
                     [1,150092,153014,3154,1,0,0.7071,0.7071],[1,149303,155406,2716,1,0,0.7071,-0.7071],\
                     [1,150084,155474,2928,1,0,0.7071,-0.7071j],[1,148850,154477,2895,1,0,0.7071,0.7071j],\
                     [1,145315,158587,49,0,1,1,0],[1,147104,158715,5218,0,1,0,1],\
                     [1,148262,158199,3088,0,1,0.7071,0.7071],[1,147844,157527,2109,0,1,0.7071,-0.7071],\
                     [1,147068,159476,2691,0,1,0.7071,-0.7071j],[1,147459,158860,2691,0,1,0.7071,0.7071j],\
                     [1,145364,160365,2912,0.7071,0.7071,1,0],[1,143902,160634,2118,0.7071,0.7071,0,1],\
                     [1,144324,160367,49,0.7071,0.7071,0.7071,0.7071],[1,143423,159909,5313,0.7071,0.7071,0.7071,-0.7071],\
                     [1,144355,159456,2525,0.7071,0.7071,0.7071,-0.7071j],[1,144453,160444,2586,0.7071,0.7071,0.7071,0.7071j],\
                     [1,151226,153521,3105,0.7071,-0.7071,1,0],[1,151338,153855,2868,0.7071,-0.7071,0,1],\
                     [1,151356,154428,5727,0.7071,-0.7071,0.7071,0.7071],[1,149152,152451,34,0.7071,-0.7071,0.7071,-0.7071],\
                     [1,149347,152377,2978,0.7071,-0.7071,0.7071,-0.7071j],[1,149757,153553,2823,0.7071,-0.7071,0.7071,0.7071j],\
                     [1,146216,157210,2795,0.7071,-0.7071j,1,0],[1,145860,156446,2474,0.7071,-0.7071j,0,1],\
                     [1,145129,156671,2969,0.7071,-0.7071j,0.7071,0.7071],[1,145461,157513,2616,0.7071,-0.7071j,0.7071,-0.7071],\
                     [1,146238,156598,5441,0.7071,-0.7071j,0.7071,-0.7071j],[1,146462,157288,29,0.7071,-0.7071j,0.7071,0.7071j],\
                     [1,150227,154954,2929,0.7071,0.7071j,1,0],[1,149428,155320,2609,0.7071,0.7071j,0,1],\
                     [1,149476,154277,3147,0.7071,0.7071j,0.7071,0.7071],[1,150337,155316,2285,0.7071,0.7071j,0.7071,-0.7071],\
                     [1,149123,153573,95,0.7071,0.7071j,0.7071,-0.7071j],[1,148216,152615,5327,0.7071,0.7071j,0.7071,0.7071j]])

intensity=[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]
#intensity=[0.972016, 0.848995, 0.980067, 0.912241, 0.860456, 0.871224, 0.916146, \
#0.936151, 0.893673, 0.926648, 0.964862, 0.859154, 0.864578, 0.853943, \
#0.85908, 0.909054, 0.925395, 0.900499, 0.956303, 0.928751, 0.991927, \
#0.881374, 0.91974, 0.93354, 0.901909, 0.982584, 0.953617, 0.879359, 0.845412, \
#0.927958, 1., 0.981409, 0.991005, 0.900439, 0.944478, 0.91525]
s1=[2442.33, 2133.22, 2462.56, 2292.14, 2162.02, 2189.07, 2301.95, 2352.21, \
2245.48, 2328.34, 2424.36, 2158.75, 2172.38, 2145.65, 2158.56, 2284.13, \
2325.19, 2262.63, 2402.85, 2333.62, 2492.36, 2214.58, 2310.98, 2345.65, \
2266.18, 2468.88, 2396.1, 2209.52, 2124.22, 2331.63, 2512.64, 2465.93, \
2490.04, 2262.48, 2373.14, 2299.7]
s2=[25717.7, 22462.8, 25930.7, 24136.2, 22766., 23050.9, 24239.5, 24768.8, \
23644.9, 24517.3, 25528.4, 22731.6, 22875.1, 22593.7, 22729.6, 24051.8, \
24484.2, 23825.5, 25302., 24573., 26244.5, 23319.5, 24334.6, 24699.7, \
23862.8, 25997.3, 25230.9, 23266.2, 22368., 24552., 26458.1, 25966.2, \
26220.1, 23823.9, 24989.1, 24215.8]
c=[628, 38, 406, 216, 224, 323, 427, 48, 319, 163, 231, 265, 739, 72, 543, 250, \
411, 456, 247, 18, 148, 124, 116, 161, 209, 14, 175, 66, 84, 113, 862, 80, \
574, 328, 393, 456]

tomo_input[:,1] = s1
tomo_input[:,2] = s2
tomo_input[:,3] = c

tomo_input=np.array([[1,0,0,256,1,0,1,0],[1,0,0,99,1,0,0,1],[1,0,0,237,1,0,0.7071,0.7071],[1,0,0,204,1,0,0.7071,-0.7071j],\
            [1,0,0,400,0,1,1,0],[1,0,0,102,0,1,0,1],[1,0,0,332,0,1,0.7071,0.7071],[1,0,0,150,0,1,0.7071,-0.7071j],\
            [1,0,0,606,0.7071,0.7071,1,0],[1,0,0,145,0.7071,0.7071,0,1],[1,0,0,500,0.7071,0.7071,0.7071,0.7071],[1,0,0,239,0.7071,0.7071,0.7071,-0.7071j],\
            [1,0,0,326,0.7071,-0.7071j,1,0],[1,0,0,32,0.7071,-0.7071j,0,1],[1,0,0,267,0.7071,-0.7071j,0.7071,0.7071],[1,0,0,181,0.7071,-0.7071j,0.7071,-0.7071j]])
#intensity=[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]

conf={'NQubits':2,'NDetectors':2,'Crosstalk':np.array([[0.9,0,0,0],[0.9,0.72,0,0],[0.9,0,0.72,0],[0.01,0.08,0.08,0.64]]),\
      'UseDerivative':0,'DoErrorEstimation':0,'DoDriftCorrection':'no','Window':[5,5,5,5],'Efficiency':[1,1,1,1]}


tomo_input=np.array([[1,0,0,0,0,1002,823,501,431,1,0,1,0],[1,0,0,0,0,421,331,872,765,1,0,0,1],[1,0,0,0,0,1032,784,376,372,1,0,0.7071,0.7071],[1,0,0,0,0,286,301,1072,821,1,0,0.7071,-0.7071],[1,0,0,0,0,656,424,978,868,1,0,0.7071,-0.7071j],[1,0,0,0,0,994,977,686,441,1,0,0.7071,0.7071j],[1,0,0,0,0,824,970,365,416,0,1,1,0],[1,0,0,0,0,314,404,717,925,0,1,0,1],[1,0,0,0,0,900,1138,412,415,0,1,0.7071,0.7071],[1,0,0,0,0,330,289,808,1036,0,1,0.7071,-0.7071],[1,0,0,0,0,315,491,773,774,0,1,0.7071,-0.7071j],[1,0,0,0,0,805,878,401,564,0,1,0.7071,0.7071j],[1,0,0,0,0,1543,330,523,280,0.7071,0.7071,1,0],[1,0,0,0,0,464,317,1589,350,0.7071,0.7071,0,1],[1,0,0,0,0,1951,425,592,295,0.7071,0.7071,0.7071,0.7071],[1,0,0,0,0,456,299,1849,470,0.7071,0.7071,0.7071,-0.7071],[1,0,0,0,0,735,271,1359,423,0.7071,0.7071,0.7071,-0.7071j],[1,0,0,0,0,1376,434,860,266,0.7071,0.7071,0.7071,0.7071j],[1,0,0,0,0,189,1591,285,583,0.7071,-0.7071,1,0],[1,0,0,0,0,327,455,190,1346,0.7071,-0.7071,0,1],[1,0,0,0,0,203,1515,223,467,0.7071,-0.7071,0.7071,0.7071],[1,0,0,0,0,299,453,282,1699,0.7071,-0.7071,0.7071,-0.7071],[1,0,0,0,0,223,711,288,1365,0.7071,-0.7071,0.7071,-0.7071j],[1,0,0,0,0,310,1335,207,752,0.7071,-0.7071,0.7071,0.7071j],[1,0,0,0,0,752,858,269,507,0.7071,-0.7071j,1,0],[1,0,0,0,0,236,537,872,952,0.7071,-0.7071j,0,1],[1,0,0,0,0,947,1198,269,484,0.7071,-0.7071j,0.7071,0.7071],[1,0,0,0,0,254,429,980,1160,0.7071,-0.7071j,0.7071,-0.7071],[1,0,0,0,0,543,568,760,1129,0.7071,-0.7071j,0.7071,-0.7071j],[1,0,0,0,0,741,1089,470,616,0.7071,-0.7071j,0.7071,0.7071j],[1,0,0,0,0,1121,954,662,316,0.7071,0.7071j,1,0],[1,0,0,0,0,586,276,1060,909,0.7071,0.7071j,0,1],[1,0,0,0,0,982,848,483,317,0.7071,0.7071j,0.7071,0.7071],[1,0,0,0,0,406,235,1018,869,0.7071,0.7071j,0.7071,-0.7071],[1,0,0,0,0,530,504,1041,815,0.7071,0.7071j,0.7071,-0.7071j],[1,0,0,0,0,952,621,465,424,0.7071,0.7071j,0.7071,0.7071j]])
intensity=[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]


rho1= np.array([[0.5238, 0.0189-0.0015j, -0.0250+0.0015j, -0.4982 + 0.0162j], [0.0189 + 0.0015j,0.0007,-0.0009-0.0000j, -0.0180-0.0009j], [-0.0250-0.0015j, -0.0009+0.0000j, 0.0012, 0.0238+0.0007j], [-0.4982-0.0162j, -0.0180+0.0009j, 0.0238-0.0007j, 0.4743]]) 

err_n = 2
# default: err_n = 100
err_functions = ['tangle','linear_entropy','entropy']
#whole function array is: ['concurrence','tangle','entanglement','entropy','linear_entropy','negativity']

part_init = 9
part = 5
times = 3


###################
## MAIN FUNCTION ##
###################

execfile('pythoneval.txt')

[rho,intensity,fval] = state_tomography(tomo_input,intensity,conf)

#print 'rho = \n'
#print rho,'\n'
#print clock()-start,'seconds elapsed. \n'



[errs,mean,mean_fid] = tomography_error(tomo_input,intensity,conf,err_functions,err_n)

#print 'Functions   = ',err_functions,'\n'
#print 'Errors      = ',errs,'\n'
#print 'Mean values = ',mean,'\n'
#print 'Mean fidelity = ',mean_fid,'\n'
#print clock()-start,'seconds elapsed. \n'

[s,a,ap,b,bp] = websiteBellsettings(rho,part_init,part,times)
res = (np.pi/2)/(part_init*(part**times))

#print 's = ',s, '\n'
#print 'a = ',a*180/np.pi,'deg \n'
#print 'ap= ',ap*180/np.pi,'deg \n'
#print 'b = ',b*180/np.pi,'deg \n'
#print 'bp= ',bp*180/np.pi,'deg \n'
#print 'resolution = ',res*180/np.pi,'deg \n'
#print clock()-start,'seconds elapsed. \n'

def createtable(M):
    s = np.shape(M)
    res = '<table boarder = "2">'
    for i in range(s[0]):
        res = add(res,' <tr>')
        for j in range(s[1]):
            res = add(res,add('  <td>',add(str(M[i,j]),'</td>')))
        res = add(res,'</tr>')
    res = add(res,'</table>')
    return res

FORREPLACE = createtable(rho)

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
for z,height in enumerate(abs(rho)):
    
    ax.bar(np.arange(4),height,zs=z,zdir='y',color='b',alpha=0.8)

plt.savefig('rhobar3')

FORREPLACE = add(FORREPLACE,'<img src="../rhobar3.png" width="500" height="500"><br>')

f = add(add(add(add('<br>Tangle ',str(mean[0])),' +/- '),str(errs[0])),'\n')
f = add(f,add(add(add(add('<br>Linear Entropy ',str(mean[1])),' +/- '),str(errs[1])),'\n'))
f = add(f,add(add(add(add('<br>Entropy ',str(mean[2])),' +/- '),str(errs[2])),'\n'))
f = add(f,add(add('<br>Intensity ',str(intensity)),'\n'))
f = add(f,add(add('<br>fval ',str(fval)),'\n'))

b = '<br>Bell state:\n'


FORREPLACE = add(FORREPLACE,f)

with open('web.html','r') as f:
    fff = '\n'.join(f.readlines())
    f.close()
print fff
fff = fff.replace('TOREPLACE', FORREPLACE)

with open('web1.html','w') as ff:
    #for line in fff:
    #    ff.write(line)
    ff.write(fff)
    ff.close()


