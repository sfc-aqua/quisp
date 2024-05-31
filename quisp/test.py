tmp = []
ans = []
cnt = 0
tmp_val = tmp[0]
for value in tmp:
    if cnt == 0:
        tmp_val = value
        cnt += 1
    else:
        if value > tmp_val:
            ans.append(value)
        else:
            ans.append(tmp_val)
        cnt = 0
print(ans)