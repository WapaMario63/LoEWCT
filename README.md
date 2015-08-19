## Legends of Equestria, Wapa Castle Team Edition

At this point, this project is now abandoned due to LoE now having an entirely different protocol, it was going to become LoEWCT2 (see [LoEWCT.tk](http://loewct.tk)), but I was not able to make a working version of the old [LoEWCT] that worked on newer clients. Another reason is that mlkj abandoned the main project long ago, plus the current person holding the most updated Private Server to date doesn't want to make public his source code.

Well, my last choice right now is remake LoEWCT entirely how lemoncest did, in Mono C#, and THEN try to port it over to Qt C++ and make the Control Panel and add those features that I have promesed in both this repository project and LoEWCT2. This will take a LONG time because now I have to learn how PNet works and try my best at remaking the server using those libraries, I belive it might be easier since they are the same ones LoE uses, but since I am now very fluent in C# (I litteraly write C# like if it were 'C++: java-like syntax edition'), this will take longer.

Oh if you ask me to make a Control Panel UI with C#, no I won't. GTK#'s Designer is just way too bad, worse than Visual Studio's, I rather use QtCreator anyday for UI designing.

I will make a LoEWCT-Sharp Repo when I have a working build! I hope I do...

If you wish to get the latest [LoEWCT] versions, you can check out my website. Keep in mind they are now known as LoE Movie Maker, since, what is the point of running a server that only supports a client that is older than a year ago? Noone would even play on it!

[LoEWCT Downloads](http://loewct.tk/downloads.php)

### Original info

[LoEWCT] is a WCT's approach at improving tux3's [LoE Private Server](http://github.com/tux3/LoE-PrivateServer) with stuff like a user friendly control panel that lets you access everything, like the chat, server console, tools to moderate players, easy configuration instead of touching .ini files, and more!

First [LoEWCT] thread on PonyForums.net: <http://ponyforums.net/showthread.php?tid=87>

A new thread will be created when the first public release of the [LoEWCT] remake is done.

This repository is made because [LoEWCT] will be written from scratch (well not really, but I am going to clean up some stuff and organize while adding new things to it).

I know I could have forked this from tux3, but since this is going to be a huge change, Id rather have my own repository without affecting the original. I DO have a forked version, but it's just there to help the original creator a little.

## Features

* An user friendly control panel with everything you need, like the console, chat, player list and more!
* Log In and Game Servers splitted into threads.
* MySQL Database integration
* Integrated with some LoE Movie Maker features
* Moderation system, other people can be mods!
* And some more things.

## FAQ

### Is this just like the one from ponyforums.net?

Nope, that one was basicly what would happen if I were to fork mlkj's repository and add/change some stuff for the better. This one however takes all that old code that is messy to work with and is more compatible with the new system I wanted to make on the original [LoEWCT].

### What is the difference between mlkj's private server, lemoncest and the old [LoEWCT] with this new [LoEWCT]?

* For mlkj's we maintain the compatability with both Babscon14, Ohaycon and August14 builds working, and also an entire new GUI.
* For lemoncest, it's way too much of a big difference I believe, since his is coded in the native language LoE was made in, Mono C#, plus his code is not yet released to the public, so I can't say anything without knowing how his server works.
* On the other hand, the old [LoEWCT], it adds lots of features that were once planned to be added on that [LoEWCT], but couldn't. See features.
