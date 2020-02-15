# If you have trouble with using xhost command
If you get this kind of error message when you use `xhost` command, 
![](https://i.imgur.com/DCM1Rd5.png)

You can fix this with
```zsh
export PATH="/opt/X11/lib$PATH"
```
