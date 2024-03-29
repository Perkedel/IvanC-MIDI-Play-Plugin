/* ==================================== JUCER_BINARY_RESOURCE ====================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#include <cstring>

namespace BinaryData
{

//================== README.md ==================
static const unsigned char temp_binary_data_0[] =
"# IvanC-MIDI-Play-Plugin\n"
" Ported the glorious JUCE MIDI loader & \"player\" plugin from https://forum.juce.com/t/playing-a-midi-file-revisited/26646 .  \n"
"I have to thancc IvanC for reproviding the source for this this majestic treasure.  \n"
"But it was incomplete & only plays single track.  \n"
"UGH! here, lemme complete this. Ah there it is.  \n"
"FULL MIDI Player in its glory! yeah! not efficient & elegant, but it works.  \n"
"Sorry, I haven't taught myself Object Oriented pure C++ fully yet, but have learned its derivatives from my college and self taughts.\n"
"\n"
" And.. I need help (Now Help Wanted: Override playhead transport). read on!\n"
"\n"
" Ahei JUCEr & Dasandimians, welcome! Please have a look & Enjoy.\n"
"\n"
"# Why some VST fail to initate correctly? like my MIDI Synth?\n"
"Because those VST are compiled in other architecture. If you have 64 bit Host, then it can't load those 32 bit VSTs at all, & vice versa.\n"
"\n"
"We have provided compile configuration for 32 bit to match with those VSTs. BUT caveat, **you also have to use 32 bit version of the host** unfortunately. \n"
"\n"
"# What's this?\n"
"This is a VSTi plugin that lets you load your favourite MIDI file then broadcast it via Event Output / MIDI OUT.\n"
"\n"
"Simply load a MIDI file, check whether you would like to play Entire Tracks, and press play on your Host / DAW.\n"
"\n"
"*COMING SOON & HELP WANTED* To allow MIDI playback without relying on Host play head.\n"
"\n"
"# Why?\n"
"Not all Plugin Host has MIDI file loading support. Despite support MIDI, but doesn't mean it's a Herman Seibb VST Host MIDI player. a.k.a. it does not have MIDI player.\n"
"\n"
"Importing MIDI as DAW track lines **is different!** that's conversion, not Loading.\n"
"\n"
"# DOWNLOAD PLS!!! I'M TIRED TO BUILD MYSELF!!! NO TIME!!!\n"
"## Right side, release section\n"
"comming soon\n"
"\n"
"## Nightly Immediately\n"
"\n"
"The nightly & cutting edge rolling is finally here!\n"
"### rendered in Visual Studio 2019\n"
"<!-- https://github.com/Perkedel/IvanC-MIDI-Play-Plugin/tree/main/Builds/VisualStudio2019/x64 (64-bit) -->\n"
"https://github.com/Perkedel/IvanC-MIDI-Play-Plugin/tree/main/Builds/VisualStudio2022/x64 (64-bit)\n"
"\n"
"- VST3\n"
"- LV2 (LADSPA v2) **(NEW)**\n"
"\n"
"# How to build\n"
"Here's how to compile this VSTi. As well as preparing everything to be able to compile more VST & JUCE projects in the future. You're welcome.\n"
"## Minus First, Get the Git & GitHub Desktop\n"
"**DO NOT DOWNLOAD ZIP**, you must legitly clone like professional.\n"
"\n"
"okay that's hard. but! there is [GitHub Desktop](https://desktop.github.com). Install it. after done, maybe restart browser.\n"
"\n"
"Now, in this GitHub repo page, scroll up from where you read this, `Code` green button, `Open in GitHub Desktop`, Select where folder you'd like to put this repo at,  \n"
"and go back to this reading. NOW! GO GO GO!\n"
"\n"
"### Note however, if you are on a platform that failed to appear `Open in GitHub Desktop`,\n"
"- Copy the `HTTPS` URL (the download tab must be selected `HTTPS`, not `SSH`) by pressing that clipboard icon button.\n"
"- Focus / Open your GitHub Desktop.\n"
"- `File` top menu.\n"
"- `Clone Repository...`.\n"
"- `URL` tab\n"
"- Paste this repo URL you've just got, in.\n"
"- Browse where you'd like to put it at.\n"
"- `Open Folder` & see that your folder selection has the repo directory name appened.\n"
"- Clone. DOne!\n"
"\n"
"Okay you're back.\n"
"\n"
"## Zeroth, You must install JUCE\n"
"https://JUCE.com yess.\n"
"\n"
"Alright, this is so confusing. Click `Discover` top left. down a bit, click `Projucer`. `Download the Projucer`. in `Personal` tier, click `Download`.  \n"
"choose your OS. now, with this ZIP file, take that `JUCE` folder to `C:/`. so now, you have `C:/JUCE` with all JUCE stuffs in it.\n"
"\n"
"idk for Linux yet. please rereach me Linux again. Oh, perhaps there are available on package managers of your distro idk.\n"
"\n"
"inside this new `JUCE` folder there is that `Projucer` executable. that, will be your project manager for JUCE things. You can create and edit projects.  \n"
"the project file is `.jucer` that put next to bunch of folders and stuffs in each project folder.\n"
"\n"
"therefore, this, you `Open Existing Project`, go to where `IvanC-MIDI-Play-Plugin.jucer` is, which is at that cloned git repo folder of `IvanC-MIDI-Play-Plugin`.\n"
"\n"
"OKAY almost forgot, **this is very important**!!! Click **person icon** top right. `Enable GNU GPL mode`! this allows you to disable splash screen even not logged in,  \n"
"declaring, I love Open Source. Remember folks, **Always share your edit forks source code if you intent to release binary file!!!** keep the same license, **GNU GPL v3** yeah!\n"
"\n"
"alright, next\n"
"\n"
"## First, grab yourself stuffs\n"
"You need following libraries first. I know, very unecessary I've defined the need for this. idk what to have & what would be in the future.\n"
"\n"
"These are not included in JUCE for legal reason. So, you need to download these all yourselves.\n"
"\n"
"### VST2, older version of VST SDK (Because you make plugin .dll, do not distribute unless you are first lucky few who got the license before deprecation)\n"
"put in anywhere you like (because it's legacy you shall not confuse with latest VST SDK, so put it in different folder than usual). \n"
"\n"
"Fill in the field for `VST (legacy) SDK` (in your Projucer global path) of e.g.: `${WHEREVER_STEINBERG_SHRINE_YOU_PUT_AT}\\vstsdk3610_11_06_2018_build_37\\VST_SDK\\VST2_SDK` .  \n"
"still don't get it? my example: I put it in *Homework* folder and inside a company name (`Steinberg`) folder (yeah every entity name gets their own folder). with that, now I fill that field with e.g.\n"
"`C:\\Users\\joelr\\Documents\\kolmorotzzet (kolmorotshitt)\\Artistic Setups\\Steinberg\\vstsdk3610_11_06_2018_build_37\\VST_SDK\\VST2_SDK`  \n"
"there you are. I hope you get it. It doesn't have to be *Homework* folder, wherever as long your NTFS (or BTRFS, ZFZ, your OS file system) & Projucer can reach it. like `C:\\SDKs\\OldVST\\VST_SDK\\VST2_SDK` stuff like that!\n"
"\n"
"Make note of the specific version `vstsdk3610_11_06_2018_build_37` according to the Juce VST2 header. you will need to find this yourselves, and due to legal issues & this repo was hosted on Earth & no Git server anywhere on other planet & no decentr"
"alized legionized Git protocol, I cannot give the forum link at the moment. I have handed this job over to Admiral Zumi.\n"
"\n"
"peck you, Steinberg!\n"
"\n"
"### ASIO.\n"
"damn it, where's the instruction. fine, you go download the ASIO SDK from https://www.steinberg.net/developers/ as well as other Steinberg's SDKs. No, **that VST SDK is new and no longer has VST2**. that one VST2 SDK folder there is empty dummy and n"
"ow it only has VST3.\n"
"\n"
"Inside this ZIP, there is that folder. pull it out into `C:\\SDKs` exactly, then rename that folder into `ASIOSDK2.3` all capital.  \n"
"The Visual Studio or whatever IDE shall see `C:\\SDKs\\ASIOSDK2.3\\Common` there.\n"
"\n"
"### AAX (EXTREMELY DANGEROUS LICENSE)\n"
"Avid is also karen!!!\n"
"- https://www.avid.com/alliance-partner-program/aax-connectivity-toolkit\n"
"- https://www.kvraudio.com/forum/viewtopic.php?t=479249\n"
"- https://forum.juce.com/t/aax-sdk-version/10513/7\n"
"- https://forum.juce.com/t/where-is-aax-sdk/21048\n"
"- https://my.avid.com/products/cppsdk?toolkit=AAX\n"
"\n"
"Go to https://www.avid.com/alliance-partner-program/aax-connectivity-toolkit, scroll down until you see that download toolkit. **REGISTER**. Accept this long paper of \xf0\x9f\x92\xa9\xf0\x9f\x92\xa9\xf0\x9f\x92\xa9\xf0\x9f\x92\xa9\xf0\x9f\x92\xa9\xf0"
"\x9f\x92\xa9\xf0\x9f\x92\xa9\xf0\x9f\x92\xa9\xf0\x9f\x92\xa9\xf0\x9f\x92\xa9\xf0\x9f\x92\xa9\xf0\x9f\x92\xa9\xf0\x9f\x92\xa9. now you're here. [scroll down to AAX](https://my.avid.com/products/cppsdk?toolkit=AAX ). Download. Look at the Projucer Glob"
"al Path, it says by default it goes to `C:\\SDKs\\AAX`.\n"
"\n"
"So with this zip file, take out that folder into `C:\\SDKs`. rename that folder into `AAX`. tada! AAX SDK installed.\n"
"\n"
"### ARA\n"
"Somehow, ARA is also available separately. However, as I've looked at it, it's licensed Apache-2.0 something something. Therefore should be safe.\n"
"- https://github.com/Celemony/ARA_SDK\n"
"\n"
"Remember, make sure that when cloning you make it recursive, meaning it also download all of the submodules installed in that repo. GitHub Desktop should do this automatically for you yay!  \n"
"Don't forget! you must `checkout` force to the stable version (`git checkout release/2.1.0 --force`), right now is tag `release/2.1.0`. Then reupdate all submodules by open terminal in that repo directory & type `git submodule update` idk. Optionally"
", you can create it as a new branch of its own if you want just to make sure the git status stable (`git switch -c 2.1.0`, the `2.1.0` is the name of the new branch).\n"
"\n"
"According to the Projucer default Global Paths, again, you clone it right in the `SDKs` folder, like `C:\\SDKs\\ARA_SDK` for Windows / ReactOS user yeah.\n"
"\n"
"## Now select your IDE export!\n"
"Watch the compile mode! I recommend you select `Release x64`. Keep in mind, 64-bit Host will not be able to load 32-bit plugin and vice versa, except when the host have the bridgers (Carla, VST Host). (jbridge is the only legit one and it's >$0 too p"
"ecking expensive!! no comment pls!! PLS MAKE ONE THAT IS $0 & OPEN SOURCE!!! IT'S BEEN YEARS NOBODY DID THIS!!!! I TRIED TO FIND ALTERNATIVES MYSELF AND GOT ZERO!!! NOBODY WORKS THE SAME WAY AS JBRIDGE)\n"
"\n"
"Build this thing! each IDE has differently set build destination. your files is the name of this project `IvanC-MIDI-Play-Plugin` in extensions of:\n"
"- `vst3` **BEST**\n"
"- `lv2` **BESTER**\n"
"- `dll` **DO NOT SHARE VST2 UNLESS YOU HAVE RARE LICENSE**\n"
"- `aax` **NOT RECOMMENDED TO SHARE UNLESS YOU HAVE PRO LICENSE**\n"
"- `au` if compiled in in macOS Xcode.\n"
"\n"
"I don't think you can export to any others, and if somehow does then idk how do we supposed to make it work.\n"
"\n"
"## With this IDE and the solution file you've opened, \n"
"**REMEMBER!!! Choose `Release` configuration!** The `Debug` is not efficient, so don't build with this configuration unless you're contributing.\n"
"\n"
"`Compile` / `Build Solution` now! usually it's `F5` or it's on Top menu of `Build`, `Compile`, etc.\n"
"\n"
"Note, it is `Build` / `Compile`, not `Run` / `Start Debugging`. This is pluggin, a `.vst3` file. `.dll` something.\n"
"\n"
"the `Standalone` version I've tested last time didn't work. so don't `Run`, just `Build` instead.\n"
"\n"
"## Now load this built binary .vst3 up into your host!\n"
"the build folder is in respective IDE where you complied at. it's named so.\n"
"\n"
"last time I see, in my case of `VisualStudio2019` and so on, it's in `x64` because I am compiling for 64-bit. So,\n"
"\n"
"`${this_source_code}/Builds/VisualStudio2019/x64` . okay yours of course can be different depending on different IDE and environment chosen.  \n"
"`${this_source_code}/Builds/${you_IDE_which_compiled_at}/x64` I think...\n"
"\n"
"Next, there is 2 folder. One because **you forgot to set the configuration correctly** (or because you want to contribute) & other that only appears if you chose correct configuration.  \n"
"there are `Debug` & `Release`. each folder appears & updates its content as you compile to which config between `Debug` & `Release`.\n"
"\n"
"use the `Release` one!\n"
"\n"
"### How to load plugins in JUCE base host typically\n"
"Find the VST manager setting.\n"
"\n"
"In kushview Element, `View` top menu, `Plugin Manager`. top left beside `Scan`, there `Option`, click it! `Scan for VST3 Plugin`.\n"
"\n"
"Bespoke, top right `vst plugins`, `manage vsts`.\n"
"\n"
"in JUCE Audio Plugin Host extras, uh... `Options` top menu, `Edit list of available plugins` (`Ctrl` + `P`).\n"
"\n"
"Now, this familiar VST manager window opens. `+` to add new folder. simply add this source code folder,  \n"
"it'l scan recursively. nvm, straight to where the `.vst3` file is at ( you might have `Debug` which is not to be used).  \n"
"\n"
"click `Save` / `Scan` . in Bespoke & JUCE Audio Plugin Host, it'll immediately scan, while kushview Element you need to press top left `Scan`.\n"
"\n"
"alright you can now add it.\n"
"\n"
"# How to use\n"
"You will need MIDI file. make sure your MIDI file has proper reset in it. Some VSTi synth such as Yamaha S-YXG2006LE in default state did not set the drum correctly. But maybe I've fixed that by putting SysEx event in 0th event. does it fixed?\n"
"\n"
"- load your MIDI VSTi synth. You can use FalcoSoft's BassMIDI VSTi to use Soundfonter (sorry, but juicy sf plugin is not full MIDI synth, it's just Soundfont tester) OR Yamaha S-YXG2006LE\n"
"- load this VSTi into the Plugin Host. For now, it works only if the Host has playhead so pls help me how to make override like [Topiary](https://forum.juce.com/t/start-midi-file-playback-from-a-plugin/31890 ) does.\n"
"- Connect `Event OUT` or `MIDI OUT` plug into another VSTi MIDI synth `Event IN` or `MIDI IN`. typically it has different color & is single than 2 others in color pair. (e.g. in Bespoke, there is orange `midi out`)\n"
"- make sure you have connected both `AUDIO_L OUT` & `AUDIO_R OUT` to each Audio out node plugs. (Bespoke has 1 cable intertwining between blue and purple, that's stereo audio, connect this to `gain` that already connected into `spliter` and then each"
" `audio` nodes) (most other hosts will require you to connect each audio plug respectively.)\n"
"- Load a MIDI file you like\n"
"- Recommended to check `Entire tracks`. this allows all tracks to be played.\n"
"- Press play on the Host! Enjoy.\n"
"- After your MIDI finish playing, stop the playhead & then reset the position. Play again or load another MIDI file.\n"
"\n"
"# Stuff I've encountered & What's wrong with those things\n"
"## Bespoke Synth\n"
"https://bespokesynth.com/ $0 & OPEN SOURCE\n"
"\n"
"This is a standalone JUCE synth, where you can build crazy music & in jams. It's like you have this DAW, get broken down to pieces, and then you got to rebuild it again. It has so many nodes you can put and connect together, and of course, it also ho"
"sts external plugins too yeah VST host!!!\n"
"\n"
"Unfortunately,:\n"
"- ~~It does not have timeline.~~ the transport over there at the moment is only to metronome internal nodes, and isn't a recognizable Playhead (`AudioTransportSource`) standardly. Without the playhead support, IvanC MIDI play does not work well and i"
"t'll just sitt there poker face unless we finally managed to have our own playhead.\n"
"- NEW correction! there is recognizable `AudioTransportSource`, but even if you press reset, it won't reset `AudioTransportPosition` position back to 0. enable `Loop` in this VSTi!!!\n"
"- Like Carla, the MIDI also screws up fatally! it fail to recognize `Program Change` and possibly others. Even tested with this finally works with loop, nope! **it forgor Program Change!!!**\n"
"\n"
"## VST Host\n"
"https://www.hermannseib.com/english/vsthost.htm $0 & PROPRIETARY\n"
"\n"
"Old yet reliable VST Host. Very famous. no need introduction. Okay this hosts VSTs, and **even VST3** as well. Plus, it has MIDI player & Audio Player in which you can sync together whoahow!!! Well then IvanC serves no purpose. However,\n"
"\n"
"Unfortunately,\n"
"- Proprietary. There is that open source variant under GNU GPL v2, but that's outdated. according to that website Herman said, people stole his work. I mean, people fork but **dare to remove the credit altogether**. what a degenerate wh88e. I wish th"
"ose thiefs jailed to this day. Hence, now we got the proprietary version that is new.\n"
"\n"
"## FalcoSoft BassMIDI Soundfont Player\n"
"http://falcosoft.hu/softwares.html#midiplayer $0 & PROPRIETARY (that BassMIDI src is just for that BassMIDI library)\n"
"\n"
"It plays MIDI yeah! You can load soundfont, because of course, it's BassMIDI. and even you can have VSTi, not just VST effect. load the VSTi with synths like Yamaha S-YXG2006LE or Roland SoundCanvas VA yeah! also if you want, you can have MIDI IN and"
" MIDI OUT to physical MIDI Synth / Virtual MIDI synth driver.\n"
"\n"
"Unfortunately,\n"
"- Proprietary. Don't be bamboozled, that `src` is only the BassMIDI library, not this player src. Yep, Freeware.\n"
"- Some screw ups special case of MIDI. If you played MIDI collected by [Astolfo Alter](https://youtu.be/UZoipDBaphk ) or [stuff edited & made by me](https://github.com/Perkedel/After-Church) (go to `RAW FILES/MIDI/JOELwindows7`, wait go back! to the "
"`RAW FILES/XG Works` yess, okay I've had some XG works experiments & edited some from [here](https://psrtutorial.com/song/yamaha.html ), click the dark blue category text to download the pack of it. try that `Electric Piano` demo I *rehacked* its cha"
"nnel 10 to program change to uhh forgot! it's new location for `Dance Kit`) first the MIDI should play fine. But if you try the same on e.g. Herman Seibb's VST Host, & Yamaha MidRadio, the Dance kit appears! it disprogram change on this FalcoSoft som"
"ehow! maybe because of Smart Drum Patch I've mentioned earlier? bug!\n"
"\n"
"## KushView Element\n"
"https://github.com/kushview/Element/ https://kushview.net/element **EXPENSIVE SELL SOUL** & Open Source\n"
"\n"
"This is newer Plugin host made with JUCE. Same as VST Host, but it utilizes JUCE powers & with foundation of JUCE. \n"
"\n"
"Unfortunately,\n"
"- EXPENSIVE!!! >$0 !!! Despite being Open Source under GNU GPL v3 (& hence the source code there on GitHub & $0), the prebuilt binaries are Expensive. worse, buying once only grants you that version. worse again, per purchase opens the download for o"
"nly 14 days! quick download before expired. worse and worst, ***RAAAAAAAAAAAAAW***, I mean, If you want to always be up to date, then you have to subscribe to their Patreon or whatever is that to have access to download link everyday for every new ve"
"rsion. Remember, don't pay for tools! and since this is considered **Adobe level of soul hostage**, it is morally correct to sparsdat this product. No offense, sorry. Oh wow, I've been canceled lmao! Well, you see that GNU GPL only wants you let peop"
"le have freedom in Source code, **but not have to be as in beer**. Bruh why not both. very flawed License I would say.\n"
"- **EGREGIOUSLY EXPENSIVE!!!!!!** Now, the permanent purchase is available, **but costs over $100!!!!!!!!!!!!!!!!**\n"
"- Lacks MIDI player at the moment. though it has Audio Player (has respond to MIDI Start, Stop, & Continue button) & duplicate its under the name of Media Player (that just plays Audio and does not respond to MIDI start stop continue button). C'mon, "
"I want MIDI player!!! This is where IvanC MIDI Play plugin.. actually honestly shines. Element has that Playhead needed.\n"
"\n"
"My question is I can fork (it's GNU GPL v3). but.. can I render and spread my own, (warning earape fx) **for $0**?  \n"
"Yes, [you can](https://www.youtube.com/watch?v=B66VtJBN2N0 ). Despite not disallowing paywall of GNU GPL, it seems that it doesn't mean anybody that rebuild & redistribute that build without official consent **~~illegal~~, no it's not**. it's **LEGAL"
"**. (among us game start sfx) HEHEHEHEHEE, yeaha boi!\n"
"\n"
"okay, give me disk space pls. little help.. no! **big help pls!!!**\n"
"\n"
"## kx.Studio Carla\n"
"https://kx.studio/Applications:Carla $0 & Open Source\n"
"\n"
"The Best Linux Audio Plugin, also available for Windows & macOS. You can host every different plugin formats & build crazy music jams, not just VST3, but also others like uhh LV2, LADSPA, etc. known too as well. Despite this machine was made with QT,"
" the VST host part utilizes JUCE whoahow! And it also has all the bridges for various formats & **ARCHITECTURES** YESS, can even load 32 bit plugins even your host is 64 bit! just like VST Host, but it's new & Open Source. Hecc, itself even can becom"
"e a plugins too as well!!!\n"
"\n"
"Unfortunately,\n"
"- The MIDI flow screws up & crap-junks alot! Now, you can try the MIDI player included and load your best MIDI file. then on left side, `Transport` tab, and press play. As you can see, it does not work well at all and seems deleted program changes an"
"d maybe others, leaving only `NoteOn` & `NoteOff` sound like. as the result, your MIDI playback sound like Piano all (in FalcoSoft's BassMIDI VSTi, it's all generic drum & Piano all) where it supposed to use MIDI's specified program changes & SysEx &"
" more. I even tried my own this IvanC MIDI Play plugin and surprise surprise, **IT'S PECKING SAME!!!** RAW & Missing Lamb Sauce!!! The Carla is the fault!!! Now how do I say my complain to the github repo issue then. let me think.\n"
"- The plugined Carla is quite finicky & crashes alot of hosts when attempted to load. What the hecc is this? multi select type of plugin? What is amalgated plugin \xf0\x9f\x98\x95\xf0\x9f\x98\x95\xf0\x9f\x98\x95\xf0\x9f\x98\x95\xf0\x9f\x98\x95\xf0\x9f"
"\xa4\xaa\xf0\x9f\xa4\xaa\xf0\x9f\xa4\xaa\xf0\x9f\xa4\xaa\xf0\x9f\x98\xb5\xe2\x80\x8d\xf0\x9f\x92\xab\xf0\x9f\x98\xb5\xe2\x80\x8d\xf0\x9f\x92\xab\xf0\x9f\x98\xb5\xe2\x80\x8d\xf0\x9f\x92\xab\xf0\x9f\x98\xb5\xe2\x80\x8d\xf0\x9f\x92\xab?\? AAA TOO HEAVY "
"I CRASH!!! Dude, if you had multiple type, have the non-amalgamated version pls! Patchbay patchbay, Rack rack, etc. 1 by 1. Did I not see it?\n"
"\n"
"## Another small things\n"
"- https://github.com/rosshoyt/MIDI-File-Player rosshoyt's MIDI Player. This is just a prototype and it's not complete FULL MIDI Player. it only loads 1 track & user selected file loading is absent (yep, compile level non-procedural hardcoded file pat"
"h). Also it only sounds the synth & not to MIDI OUT. Well, trying to implement its threaded way doesn't work with Plugin type of project, that way only works for that type (Desktop GUI Application). I tried it. look at commented.\n"
"- https://sites.google.com/site/zarkoasenov/zerovjane https://www.kvraudio.com/forum/viewtopic.php?t=438406&start=15 Unfortunately, the MIDI player seems no longer working with our VST host we have here.\n"
"- https://code.google.com/archive/p/pizmidi/downloads https://www.kvraudio.com/product/midilooper-by-insert-piz-here While it's fully functional even that `DEMO VERSION`, it's still not work as I expected when I try to load the MIDI to there. This is"
" just a basic press key Sequencer, not a valid MIDI Player that got more than this.\n"
"- https://jstuff.wordpress.com jbridge is bridge generator for each VST dll. put your other architecture VST here, and you'll have bridged to your archicture VST. This is very expensive & I am appalled that nobody want to build $0 & Open Source compe"
"ting alternative to this. This is why I have to still support 32-bit, for it this.. ugh!!! stop canceling! We got age old trouble been unsolved for centuries!!! don't sit right there complaining me complaining that there is age old pecking paywall th"
"at remains unbroken forever!!!. Not to mention, everytime the bridged version loads, it complains lack of Admin privilege on the Host execution. wtf!? shut up!!!\n"
"\n"
"# Damn, where home should I go?\n"
"Nowhere I can peacefully rely on Host!? We only have kuzu / OpenMIDIProject MIDI Tester & Sekaiju but uh now, kuzu became trouble-heads. No, not NFT, it was the paid DLC. Sekaiju Script is not $0. other than that, Sekaiju is fully functional. also MI"
"DI Tester is completely functional. But, them both only send event to MIDI OUT, no VST Hosting support.  \n"
"LINK PLS!!!\n"
"\n"
"C'mon, I need help. I've been trying to build on playhead here, because of of all VST Host I can be in peace is **Bespoke Synth**. But it lacks recognizable play head transport by nature of design and goal of that JUCE synth. This is why I need pecki"
"ng need help to figure how do we supposed to own play head here, in Audio Plugin type of JUCE project.\n"
"\n"
"JUST, **That**, one Play head inside this our VSTi, so we together can use Bespoke to build craziest ever MIDI Player. Not just Surreal randomness, but ordered & Timelined MIDI playback as well!\n"
"\n"
"I tried every single way I could find with search, and none of those all works.\n"
"\n"
"# TODO\n"
"## Install JUCE source code itself modules but it's LV2 fork\n"
"https://github.com/lv2-porting-project/JUCE/tree/lv2  \n"
"https://jatinchowdhury18.medium.com/building-lv2-plugins-with-juce-and-cmake-d1f8937dbac3  \n"
"\n"
"I am surprised JUCE does not yet support rendering / compilation to LADSPA v2! what the peck?!\n"
"\n"
"simply have a `modules` folder, `git submodules add https://github.com/lv2-porting-project/JUCE/ `  \n"
"and then checkout / change branch of that submodule into `lv2` branch instead of master with go to that `JUCE` special module folder,  \n"
"and then `git checkout lv2`.\n"
"\n"
"maybe later.";

const char* README_md = (const char*) temp_binary_data_0;


const char* getNamedResource (const char* resourceNameUTF8, int& numBytes);
const char* getNamedResource (const char* resourceNameUTF8, int& numBytes)
{
    unsigned int hash = 0;

    if (resourceNameUTF8 != nullptr)
        while (*resourceNameUTF8 != 0)
            hash = 31 * hash + (unsigned int) *resourceNameUTF8++;

    switch (hash)
    {
        case 0x64791dc8:  numBytes = 23370; return README_md;
        default: break;
    }

    numBytes = 0;
    return nullptr;
}

const char* namedResourceList[] =
{
    "README_md"
};

const char* originalFilenames[] =
{
    "README.md"
};

const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8)
{
    for (unsigned int i = 0; i < (sizeof (namedResourceList) / sizeof (namedResourceList[0])); ++i)
        if (strcmp (namedResourceList[i], resourceNameUTF8) == 0)
            return originalFilenames[i];

    return nullptr;
}

}
