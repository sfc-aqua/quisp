if type "brew" > /dev/null 2>&1; then
    echo "brew already installed"
else
    echo "We couldn't find brew in your system. Can I install it?"
    echo "yes/no"
    read inputs

    if [-z $input]; then
    echo "Input not recognized"
    elif [ $input = 'yes' ] || [ $input = 'YES' ] || [ $input = 'y' ] ; then
        echo "Install brew"
        /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install.sh)"
    elif [ $input = 'no' ] || [ $input = 'NO' ] || [ $input = 'n' ] ; then
        echo "OK, finish script"
        exit 1
    else
        echo "Input yes or no"
    ConfirmExecution
  fi
fi

if type "docker" > /dev/null 2>&1; then
    echo "docker already installed"
else
    brew install docker
    brew cask install docker
fi

if type "socat" > /dev/null 2>&1; then
    echo "socat already installed"
else
    brew install socat
fi

if type "xterm" > /dev/null 2>&1; then
    echo "xterm already installed"
else
    brew cask install xquartz
fi

echo "All tools are successfully installed! Don't forget to reboot your laptop!" 
