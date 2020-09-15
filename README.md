# computer_vision_realsense  
Experimenting with the Intel Realsense D series RGB-D cameras  


# OpenCV setup:  

Clone OpenCV: https://github.com/opencv/opencv  
Clone OpenCV Mods: https://github.com/opencv/opencv_contrib    

**Cmake: **  
Source is /opencv/  
Build to a new "build" folder  
Configure: Select your version of Visual Studio (takes a few seconds)  
 ... Set 'Path' to /opencv_contrib/modules    

Open the VS solution file in new 'Build' directory:  
We can build both debug and release versions of the library. (This takes several minutes, release takes even longer.)  

Now, in VS, go to `/CMakeTargets/INSTALL` and right click, then `'Build' ` 

New directory called `'Install'` contains our build files. =)  

Add the `\opencv\x64\vc16\bin` path to environmental variables:  