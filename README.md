# emacspeak-speechd

This project is an experiment to use Speech Dispatcher with [Emacspeak](https://github.com/tvraman/emacspeak).

## How to use

Clone this repository:
```
$ git clone https://github.com/taniodev/emacspeak-speechd.git
$ cd emacspeak-speechd/
```

Build the library (you need the TCL and Speech Dispatcher libraries):
```
$ make
```

Copy the files to emacspeak servers directory:
```
$ mkdir <EMACSPEAK_PATH>/servers/linux-speechd
$ cp linux-speechd/tclspeechd.so <EMACSPEAK_PATH>/servers/linux-speechd/
$ cp speechd <EMACSPEAK_PATH>/servers/
```

Check if **speechd** is working:
```
$ cd <EMACSPEAK_PATH>/servers/
$ ./speechd
tts_say {Hello World!}
exit
```

Set the **DTK_PROGRAM** and start Emacs:
```
$ export DTK_PROGRAM="speechd"
$ emacs
```

## Some settings

You can edit the **speechd** file to change the output module, volume and more.

