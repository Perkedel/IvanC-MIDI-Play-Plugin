# IvanC-MIDI-Play-Plugin
 Ported the glorious JUCE MIDI loader & "player" plugin from https://forum.juce.com/t/playing-a-midi-file-revisited/26646 .  
I have to thancc IvanC for reproviding the source for this this majestic treasure.  
But it was incomplete & only plays single track.  
UGH! here, lemme complete this. Ah there it is.  
FULL MIDI Player in its glory! yeah! not efficient & elegant, but it works.  
Sorry, I haven't taught myself Object Oriented pure C++ fully yet, but have learned its derivatives from my college and self taughts.

 And.. I need help (Now Help Wanted: Override playhead transport). read on!

 Ahei JUCEr & Dasandimians, welcome! Please have a look & Enjoy.

# Why some VST fail to initate correctly? like my MIDI Synth?
Because those VST are compiled in other architecture. If you have 64 bit Host, then it can't load those 32 bit VSTs at all, & vice versa.

We have provided compile configuration for 32 bit to match with those VSTs. BUT caveat, **you also have to use 32 bit version of the host** unfortunately. 

# What's this?
This is a VSTi plugin that lets you load your favourite MIDI file then broadcast it via Event Output / MIDI OUT.

Simply load a MIDI file, check whether you would like to play Entire Tracks, and press play on your Host / DAW.

*COMING SOON & HELP WANTED* To allow MIDI playback without relying on Host play head.

# Why?
Not all Plugin Host has MIDI file loading support. Despite support MIDI, but doesn't mean it's a Herman Seibb VST Host MIDI player. a.k.a. it does not have MIDI player.

Importing MIDI as DAW track lines **is different!** that's conversion, not Loading.

# How to build
## First, grab yourself stuffs
### VST2, older version of VST SDK (Because you make plugin .dll, do not distribute unless you are first lucky few who got the license before deprecation)
put in anywhere you like (because it's legacy you shall not confuse with latest VST SDK, so put it in different folder than usual). 

Fill in the field for `VST (legacy) SDK` (in your Projucer global path) of e.g.: `${WHEREVER_STEINBERG_SHRINE_YOU_PUT_AT}\vstsdk3610_11_06_2018_build_37\VST_SDK\VST2_SDK` .  
still don't get it? my example: I put it in *Homework* folder and inside a company name (`Steinberg`) folder (yeah every entity name gets their own folder). with that, now I fill that field with e.g.
`C:\Users\joelr\Documents\kolmorotzzet (kolmorotshitt)\Artistic Setups\Steinberg\vstsdk3610_11_06_2018_build_37\VST_SDK\VST2_SDK`  
there you are. I hope you get it. It doesn't have to be *Homework* folder, wherever as long your NTFS (or BTRFS, ZFZ, your OS file system) & Projucer can reach it. like `C:\SDKs\OldVST\VST_SDK\VST2_SDK` stuff like that!

Make note of the specific version `vstsdk3610_11_06_2018_build_37` according to the Juce VST2 header. you will need to find this yourselves, and due to legal issues & this repo was hosted on Earth & no Git server anywhere on other planet & no decentralized legionized Git protocol, I cannot give the forum link at the moment. I have handed this job over to Admiral Zumi.

peck you, Steinberg!

### ASIO.
damn it, where's the instruction. fine, you go download the ASIO SDK from https://www.steinberg.net/developers/ as well as other Steinberg's SDKs. No, **that VST SDK is new and no longer has VST2**. that one VST2 SDK folder there is empty dummy and now it only has VST3.

Inside this ZIP, there is that folder. pull it out into `C:\SDKs` exactly, then rename that folder into `ASIOSDK2.3` all capital.  
The Visual Studio or whatever IDE shall see `C:\SDKs\ASIOSDK2.3\Common` there.

### AAX (EXTREMELY DANGEROUS LICENSE)
Avid is also karen!!!
- https://www.avid.com/alliance-partner-program/aax-connectivity-toolkit
- https://www.kvraudio.com/forum/viewtopic.php?t=479249
- https://forum.juce.com/t/aax-sdk-version/10513/7
- https://forum.juce.com/t/where-is-aax-sdk/21048
- https://my.avid.com/products/cppsdk?toolkit=AAX

Go to https://www.avid.com/alliance-partner-program/aax-connectivity-toolkit, scroll down until you see that download toolkit. **REGISTER**. Accept this long paper of 💩💩💩💩💩💩💩💩💩💩💩💩💩. now you're here. [scroll down to AAX](https://my.avid.com/products/cppsdk?toolkit=AAX ). Download. Look at the Projucer Global Path, it says by default it goes to `C:\SDKs\AAX`.

So with this zip file, take out that folder into `C:\SDKs`. rename that folder into `AAX`. tada! AAX SDK installed.

## Now select your IDE export!
Watch the compile mode! I recommend you select `Release x64`. Keep in mind, 64-bit Host will not be able to load 32-bit plugin and vice versa, except when the host have the bridgers (Carla, VST Host). (jbridge is the only legit one and it's >$0 too pecking expensive!! no comment pls!! PLS MAKE ONE THAT IS $0 & OPEN SOURCE!!! IT'S BEEN YEARS NOBODY DID THIS!!!! I TRIED TO FIND ALTERNATIVES MYSELF AND GOT ZERO!!! NOBODY WORKS THE SAME WAY AS JBRIDGE)

Build this thing! each IDE has differently set build destination. your files is the name of this project `IvanC-MIDI-Play-Plugin` in extensions of:
- `vst3` **BEST**
- `dll` **DO NOT SHARE VST2 UNLESS YOU HAVE RARE LICENSE**
- `aax` **NOT RECOMMENDED TO SHARE UNLESS YOU HAVE PRO LICENSE**
- `au` if compiled in in macOS Xcode.

I don't think you can export to any others, and if somehow does then idk how do we supposed to make it work.

# How to use
You will need MIDI file. make sure your MIDI file has proper reset in it. Some VSTi synth such as Yamaha S-YXG2006LE in default state did not set the drum correctly. But maybe I've fixed that by putting SysEx event in 0th event. does it fixed?

- load your MIDI VSTi synth. You can use FalcoSoft's BassMIDI VSTi to use Soundfonter (sorry, but juicy sf plugin is not full MIDI synth, it's just Soundfont tester) OR Yamaha S-YXG2006LE
- load this VSTi into the Plugin Host. For now, it works only if the Host has playhead so pls help me how to make override like [Topiary](https://forum.juce.com/t/start-midi-file-playback-from-a-plugin/31890 ) does.
- Connect `Event OUT` or `MIDI OUT` plug into another VSTi MIDI synth `Event IN` or `MIDI IN`. typically it has different color & is single than 2 others in color pair. (e.g. in Bespoke, there is orange `midi out`)
- make sure you have connected both `AUDIO_L OUT` & `AUDIO_R OUT` to each Audio out node plugs. (Bespoke has 1 cable intertwining between blue and purple, that's stereo audio, connect this to `gain` that already connected into `spliter` and then each `audio` nodes) (most other hosts will require you to connect each audio plug respectively.)
- Load a MIDI file you like
- Recommended to check `Entire tracks`. this allows all tracks to be played.
- Press play on the Host! Enjoy.
- After your MIDI finish playing, stop the playhead & then reset the position. Play again or load another MIDI file.

# Stuff I've encountered & What's wrong with those things
## Bespoke Synth
https://bespokesynth.com/ $0 & OPEN SOURCE

This is a standalone JUCE synth, where you can build crazy music & in jams. It's like you have this DAW, get broken down to pieces, and then you got to rebuild it again. It has so many nodes you can put and connect together, and of course, it also hosts external plugins too yeah VST host!!!

Unfortunately,:
- It does not have timeline. the transport over there at the moment is only to metronome internal nodes, and isn't a recognizable Playhead (`AudioTransportSource`) standardly. Without the playhead support, IvanC MIDI play does not work well and it'll just sitt there poker face unless we finally managed to have our own playhead.

## VST Host
https://www.hermannseib.com/english/vsthost.htm $0 & PROPRIETARY

Old yet reliable VST Host. Very famous. no need introduction. Okay this hosts VSTs, and **even VST3** as well. Plus, it has MIDI player & Audio Player in which you can sync together whoahow!!! Well then IvanC serves no purpose. However,

Unfortunately,
- Proprietary. There is that open source variant under GNU GPL v2, but that's outdated. according to that website Herman said, people stole his work. I mean, people fork but **dare to remove the credit altogether**. what a degenerate wh88e. I wish those thiefs jailed to this day. Hence, now we got the proprietary version that is new.

## FalcoSoft BassMIDI Player
LINK $0 & PROPRIETARY (that BassMIDI src is just for that BassMIDI library)

It plays MIDI yeah! You can load soundfont, because of course, it's BassMIDI. and even you can have VSTi, not just VST effect. load the VSTi with synths like Yamaha S-YXG2006LE or Roland SoundCanvas VA yeah! also if you want, you can have MIDI IN and MIDI OUT to physical MIDI Synth / Virtual MIDI synth driver.

Unfortunately,
- Proprietary. Don't be bamboozled, that src is only the BassMIDI library, not this player src. Yep, Freeware.
- Some screw ups special case of MIDI. If you played MIDI collected by [Astolfo Alter](https://youtu.be/UZoipDBaphk ) or [stuff edited & made by me](https://github.com/Perkedel/After-Church) (go to `RAW FILES/MIDI/JOELwindows7`, wait go back! to the `RAW FILES/XG Works` yess, okay I've had some XG works experiments & edited some from [here](https://psrtutorial.com/song/yamaha.html ), click the dark blue category text to download the pack of it. try that `Electric Piano` demo I *rehacked* its channel 10 to program change to uhh forgot! it's new location for `Dance Kit`) first the MIDI should play fine. But if you try the same on e.g. Herman Seibb's VST Host, & Yamaha MidRadio, the Dance kit appears! it disprogram change on this FalcoSoft somehow! maybe because of Smart Drum Patch I've mentioned earlier? bug!

## KushView Element
https://github.com/kushview/Element/ https://kushview.net/element **EXPENSIVE SELL SOUL** & Open Source

This is newer Plugin host made with JUCE. Same as VST Host, but it utilizes JUCE powers & with foundation of JUCE. 

Unfortunately,
- EXPENSIVE!!! >$0 !!! Despite being Open Source under GNU GPL v3 (& hence the source code there on GitHub & $0), the prebuilt binaries are Expensive. worse, buying once only grants you that version. worse again, per purchase opens the download for only 14 days! quick download before expired. worse and worst, ***RAAAAAAAAAAAAAW***, I mean, If you want to always be up to date, then you have to subscribe to their Patreon or whatever is that to have access to download link everyday for every new version. Remember, don't pay for tools! and since this is considered **Adobe level of soul hostage**, it is morally correct to sparsdat this product. No offense, sorry. Oh wow, I've been canceled lmao! Well, you see that GNU GPL only wants you let people have freedom in Source code, **but not have to be as in beer**. Bruh why not both. very flawed License I would say.
- Lacks MIDI player at the moment. though it has Audio Player (has respond to MIDI Start, Stop, & Continue button) & duplicate its under the name of Media Player (that just plays Audio and does not respond to MIDI start stop continue button). C'mon, I want MIDI player!!! This is where IvanC MIDI Play plugin.. actually honestly shines. Element has that Playhead needed.

My question is I can fork (it's GNU GPL v3). but.. can I render and spread my own, (warning earape fx) **for $0**?

## kx.Studio Carla
https://kx.studio/Applications:Carla $0 & Open Source

The Best Linux Audio Plugin, also available for Windows & macOS. You can host every different plugin formats & build crazy music jams, not just VST3, but also others like uhh LV2, LADSPA, etc. known too as well. Despite this machine was made with QT, the VST host part utilizes JUCE whoahow! And it also has all the bridges for various formats & **ARCHITECTURES** YESS, can even load 32 bit plugins even your host is 64 bit! just like VST Host, but it's new & Open Source. Hecc, itself even can become a plugins too as well!!!

Unfortunately,
- The MIDI flow screws up & crap-junks alot! Now, you can try the MIDI player included and load your best MIDI file. then on left side, `Transport` tab, and press play. As you can see, it does not work well at all and seems deleted program changes and maybe others, leaving only `NoteOn` & `NoteOff` sound like. as the result, your MIDI playback sound like Piano all (in FalcoSoft's BassMIDI VSTi, it's all generic drum & Piano all) where it supposed to use MIDI's specified program changes & SysEx & more. I even tried my own this IvanC MIDI Play plugin and surprise surprise, **IT'S PECKING SAME!!!** RAW & Missing Lamb Sauce!!! The Carla is the fault!!! Now how do I say my complain to the github repo issue then. let me think.
- The plugined Carla is quite finicky & crashes alot of hosts when attempted to load. What the hecc is this? multi select type of plugin? What is amalgated plugin 😕😕😕😕😕🤪🤪🤪🤪😵‍💫😵‍💫😵‍💫😵‍💫?? AAA TOO HEAVY I CRASH!!! Dude, if you had multiple type, have the non-amalgamated version pls! Patchbay patchbay, Rack rack, etc. 1 by 1. Did I not see it?

## Another small things
- https://github.com/rosshoyt/MIDI-File-Player rosshoyt's MIDI Player. This is just a prototype and it's not complete FULL MIDI Player. it only loads 1 track & user selected file loading is absent (yep, compile level non-procedural hardcoded file path). Also it only sounds the synth & not to MIDI OUT. Well, trying to implement its threaded way doesn't work with Plugin type of project, that way only works for that type (Desktop GUI Application). I tried it. look at commented.
- https://sites.google.com/site/zarkoasenov/zerovjane https://www.kvraudio.com/forum/viewtopic.php?t=438406&start=15 Unfortunately, the MIDI player seems no longer working with our VST host we have here.
- https://code.google.com/archive/p/pizmidi/downloads https://www.kvraudio.com/product/midilooper-by-insert-piz-here While it's fully functional even that `DEMO VERSION`, it's still not work as I expected when I try to load the MIDI to there. This is just a basic press key Sequencer, not a valid MIDI Player that got more than this.
- https://jstuff.wordpress.com jbridge is bridge generator for each VST dll. put your other architecture VST here, and you'll have bridged to your archicture VST. This is very expensive & I am appalled that nobody want to build $0 & Open Source competing alternative to this. This is why I have to still support 32-bit, for it this.. ugh!!! stop canceling! We got age old trouble been unsolved for centuries!!! don't sit right there complaining me complaining that there is age old pecking paywall that remains unbroken forever!!!. Not to mention, everytime the bridged version loads, it complains lack of Admin privilege on the Host execution. wtf!? shut up!!!

# Damn, where home should I go?
Nowhere I can peacefully rely on Host!? We only have kuzu / OpenMIDIProject MIDI Tester & Sekaiju but uh now, kuzu became trouble-heads. No, not NFT, it was the paid DLC. Sekaiju Script is not $0. other than that, Sekaiju is fully functional. also MIDI Tester is completely functional. But, them both only send event to MIDI OUT, no VST Hosting support.  
LINK PLS!!!

C'mon, I need help. I've been trying to build on playhead here, because of of all VST Host I can be in peace is **Bespoke Synth**. But it lacks recognizable play head transport by nature of design and goal of that JUCE synth. This is why I need pecking need help to figure how do we supposed to own play head here, in Audio Plugin type of JUCE project.

JUST, **That**, one Play head inside this our VSTi, so we together can use Bespoke to build craziest ever MIDI Player. Not just Surreal randomness, but ordered & Timelined MIDI playback as well!

I tried every single way I could find with search, and none of those all works.