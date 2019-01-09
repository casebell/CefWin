# CefWin
A C++ wrapper for simple access to cromium embedded framework
## Links
```https://bitbucket.org/chromiumembedded/cef```

download page:
```http://opensource.spotify.com/cefbuilds/index.html```


## Preparing
download windows 64bit Standard Distribution

extract to ```...\source\repos```

Rename ```...\source\repos\cef_binary_...64``` to ```...\source\repos\cef64``` 

### Create Visula Studio Projects

Start native tools command prompt and navigate to ```...\source\repos\cef64``` 

```
cmake -G "Visual Studio 15" -A x64
```

### Compile samples

Open solution in Visual Studio, rebuild all and start Sample program

## Prepare CefWin

Clone Repository to ```...\source\repos\cef64```