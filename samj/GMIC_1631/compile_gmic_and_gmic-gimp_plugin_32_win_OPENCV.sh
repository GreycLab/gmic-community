
#############################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################
####
####
#### Script "compile_gmic_and_gmic-gimp_plugin_32_win.sh" pour compiler GMIC et le plugin G'MIC pour Gimp avec les sources de SourceForge 
#### Ce script est très simple :
####	- Il compile le plug-in.
####	- Il crée l'environnement complet du greffon dans le répertoire GMIC-GIMP-PLUGIN-32bit-WIN (en écrasant le répertoire existant).
####	- Il crée l'environnement complet de GMIC dans le répertoire GMIC-32bit-WIN (en écrasant le répertoire existant).
####	- Il crée l'archive gmic_gmic-gimp_win32.tar.xz 
#### 
#### Ce script "compile_gmic_and_gmic-gimp_plugin_32_win_gcc481.sh" fonctionne avec l'environnement de compilation 32 bits Windows disponible sur : http://www.aljacom.com/~gimp/petit-msys-mingw-gimp28.7z
#### Il faut l'installer dans "C:\petit-msys-mingw-gimp28".
#### Ce srcipt utilise GCC 4.9.2 qui doit être installé dans le répertoire "C:\petit-msys-mingw-gimp28" . Il faut obtenir "C:\petit-msys-mingw-gimp28\gcc492\mingw32\bin\i686-w64-mingw32-g++.exe"
####
#### Utilisation :
####	- Démarrer MSYS en cliquant sur "start_MSYS_GCC492.bat".
####    - Éditer ce fichier et modifier les variables : Stable="yes"  ou   Stable="no"  et  version_gmic=\"samj_20150414\"
####	- Entrer les deux lignes de commandes qui suivent.
####			cd /env
####			./compile_gmic_and_gmic-gimp_plugin_32_win.sh
####	- Il y a 66 opérations à effectuer. Attendre le message "FIN - END".
####	- L'ensemple pour faire fonctionner le plug-in est disponible dans le répertoire "GMIC-GIMP-PLUGIN-32bit-WIN" ( C:\petit-msys-mingw-gimp28\GMIC-GIMP-PLUGIN-32bit-WIN ).
####	- L'ensemple pour faire fonctionner GMIC disponible dans le répertoire "GMIC-32bit-WIN" ( C:\petit-msys-mingw-gimp28\GMIC-32bit-WIN ).
####
####
#### _______________________________________________________________________________________________________________________________________________________________________________________________
####
#### English translation
####
#### Script "compile_gmic_and_gmic-gimp_plugin_32_win.sh" to compile GMIC and the plugin G'MIC for Gimp with sources from SourceForge
#### This script is very simple:
####
####	- It compiles the plugin.
####	- It creates the entire environment for the plug-in in the "GMIC-GIMP-PLUGIN-32bit-WIN" directory (overwriting the existing directory)
####	- It creates the archive gmic_gmic-gimp_win32.tar.xz 
####
#### This script "compile_gmic_and_gmic-gimp_plugin_32_win.sh" works with 32-bit build environment for Windows available :  http://www.aljacom.com/~gimp/petit-msys-mingw-gimp28.7z
#### It must be installed in "C:\petit-msys-mingw-gimp28".
#### This srcipt using GCC 4.9.2 to be installed in the directory "C:\petit-msys-mingw-gimp28" . Must be obtained "C:\petit-msys-mingw-gimp28\gcc492\mingw32\bin\i686-w64-mingw32-g++.exe"
####
#### Use:
####    - Check the value of the variable "Repertoire_Source" in this file.
####    - Edit this file, set correct values of the variables : Stable="yes"  or   Stable="no"  and  version_gmic=\"samj_20150414\"
####	- Start MSYS clicking "start_MSYS_GCC492.bat".
####	- Enter the two command lines that follow.
####			cd /env
####			./compile_gmic_and_gmic-gimp_plugin_32_win.sh
####	- There are 66 operations to be performed. Wait for the message "FIN - END".
####	- The plug-in is available in the "GMIC-GIMP-PLUGIN-32bit-WIN" directory ( C:\petit-msys-mingw-gimp28\GMIC-GIMP-PLUGIN-32bit-WIN ).
####	- GMIC is available in the "GMIC-32bit-WIN" directory ( C:\petit-msys-mingw-gimp28\GMIC-32bit-WIN ).
####
####
#### version 17  20150414  par samj le 14 avril 2015     Ajouts -Dgmic_gimp  $commande_version=$version_gmic - Ajouts variables   Stable="yes"  ou   Stable="no"  et  version_gmic=\"samj_20150414\"
#### version 16  20150405  par samj le 5 avril 2015      Pâques, ajouts -DPSAPI_VERSION=1 et -lpsapi et -std=c++11 pour le plug-in ( https://msdn.microsoft.com/en-us/library/windows/desktop/ms682050(v=vs.85).aspx )
#### version 15  20150228  par samj le 28 février 2015   gcc 4.9.2 
#### version 14  20150219  par samj le 19 février 2015   Ajout pour G'MIC en lignes de commandes et Gimp plug-in -Dcimg_use_curl -lcurl . L'exécutable curl.exe est supprimé.
#### version 13  20150208  par samj le 8 février 2015    Ajout gmicol
#### version 12  20141204  par samj le 4 décembre 2014   Ajouts des 2 DLL msvcp120.dll et msvcr120.dll du runtime Visual C++ de Microsoft
#### version 11  20141202  par samj le 2 décembre 2014   Ajouts  OpenCV et -Dcimg_verbosity=3 -g
#### version 10  20141013  par samj le 13 octobre 2014   Modifications pour G'MIC 1.6.0.2 beta . Modification de -Dcimg_display pour le plug-in.
#### version 9   20140822  par samj le 22 août 2014      Modifications pour G'MIC 1.6.0.1 . Ajouts -Dgmic_main -lgomp -std=c++11 . Supprimer : GIT , -Dgmic_float_only pour plug-in , compilation des fichiers gmic_bool.o gmic_uchar.o gmic_char.o gmic_ushort.o gmic_short.o gmic_uint.o gmic_int.o gmic_ulong.o gmic_long.o gmic_float.o gmic_double.o
#### version 8   20140702  par samj le 2 juillet 2014    Ajouts gmic_ulong.o gmic_long.o
#### version 7   20140616  par samj le 16 juin 2014      supprimer -Dgmic_use_openmp
#### version 6   20140610  par samj le 10 juin 2014      -Dcimg_use_openmp
#### version 5   20140608  par samj le 8 juin 2014       Ajout -fopenmp -Dcimg_use_openmp libgomp-1.dll libwinpthread-1.dll gcc 4.9.0
#### version 4   20140211  par samj le 11 février 2014   Correction (2 commandes identiques sur culr.exe). Remarque : Remplacer si nécessaire la DLL libfftw3-3.dll par une version d'origine disponible sur ftp://ftp.fftw.org/pub/fftw/fftw-3.3.3-dll32.zip
#### version 3   20140127  par samj le 27 janvier 2014   Ajout -Dgmic_check_image
#### version 2   20140115  par samj le 15 janvier 2014   Ajout pour g'mic en ligne de commande  libwinpthread-1.dll
#### version 1   20140104  par samj le  4 janvier 2014
####
####
####
#############################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################









#### Compilation de GMIC et du plug-in, création de l'archive gmic_gmic-gimp_win32.tar.xz 


Stable="no"
####Stable="yes"

version_gmic=\"Test\"


if [[ $Stable == "yes" ]]
	then 
		#### en attente d'un flag pour version stable
		commande_version=-std
		version_gmic=c++11
else		
		commande_version=-Dgmic_prerelease
fi


echo $commande_version=$version_gmic



Nombre_Operations=66
Repertoire_Source=/env/gmic/src
Repertoire_Plugin=/env/GMIC-GIMP-PLUGIN-32bit-WIN
Repertoire_GMIC=/env/GMIC-32bit-WIN


echo 01/$Nombre_Operations
cd $Repertoire_Source

echo 02/$Nombre_Operations
/env/gcc492/mingw32/bin/i686-w64-mingw32-g++.exe -o gmic_gimp.o -c gmic.cpp -fopenmp -Dcimg_use_curl -Dcimg_use_openmp -Dgmic_build -DPSAPI_VERSION=1 -Dgmic_gimp $commande_version=$version_gmic -std=c++11 -I/env/gcc492/mingw32/include -I/env/gcc492/mingw32/i686-w64-mingw32/include -I/mingw/include -I/python/include -pipe -O3 -mms-bitfields -march=i686 -s -Wall -W -mtune=generic -Dcimg_use_vt100 -Dgmic_is_parallel -Dgmic_is_beta=1 -Dcimg_use_fftw3 -Dcimg_use_png -Dcimg_use_zlib -Dcimg_use_tiff -Dcimg_use_jpeg -Dcimg_display=2 -Dcimg_use_rng -Dgmic_gimp -Dgmic_check_image

echo 03/$Nombre_Operations
/env/gcc492/mingw32/bin/i686-w64-mingw32-g++.exe -o gmic_gimp.exe gmic_gimp.cpp gmic_gimp.o -fopenmp -Dcimg_use_curl -Dcimg_use_openmp `gimptool-2.0.exe --cflags` -Dgmic_build  -DPSAPI_VERSION=1 -Dgmic_gimp $commande_version=$version_gmic -std=c++11 -I/env/gcc492/mingw32/include -I/env/gcc492/mingw32/i686-w64-mingw32/include -I/mingw/include -I/python/include -pipe -O3 -mms-bitfields -march=i686 -s -Wall -W -mtune=generic -Dcimg_use_vt100 -Dgmic_is_parallel -Dgmic_is_beta=1 -Dcimg_use_fftw3 -Dcimg_use_png -Dcimg_use_zlib -Dcimg_use_tiff -Dcimg_use_jpeg -Dcimg_use_vt100 -Dcimg_display=2 -Dcimg_use_rng -Dgmic_check_image `gimptool-2.0.exe --libs` -L/env/gcc492/mingw32/lib -L/env/gcc492/mingw32/i686-w64-mingw32/lib -L/mingw/lib -mwindows -lpthread -lm -lfftw3 -lpng16 -lz -ltiff -ljpeg -lgomp -lcurl -lpsapi 

echo 04/$Nombre_Operations
#### temporisation...
/env/gcc492/mingw32/bin/strip.exe -V
/env/gcc492/mingw32/bin/strip.exe gmic_gimp.exe


echo 05/$Nombre_Operations
rm -f -r $Repertoire_Plugin

echo 06/$Nombre_Operations
mkdir $Repertoire_Plugin

#### echo 07/$Nombre_Operations
#### mkdir $Repertoire_Plugin/_gmic

echo 07/$Nombre_Operations
cp /env/gcc492/mingw32/bin/libgomp-1.dll $Repertoire_Plugin

echo 08/$Nombre_Operations
cp /env/gcc492/mingw32/bin/libwinpthread-1.dll $Repertoire_Plugin

echo 09/$Nombre_Operations
cp /mingw/bin/libfftw3-3.dll $Repertoire_Plugin

echo 10/$Nombre_Operations
cp /env/gcc492/mingw32/bin/libgcc_s_dw2-1.dll $Repertoire_Plugin

echo 11/$Nombre_Operations
cp /mingw/bin/libjpeg-9.dll $Repertoire_Plugin

echo 12/$Nombre_Operations
cp /mingw/bin/liblzma-5.dll $Repertoire_Plugin

echo 13/$Nombre_Operations
cp /mingw/bin/libpng16-16.dll $Repertoire_Plugin

echo 14/$Nombre_Operations
cp /env/gcc492/mingw32/bin/libstdc++-6.dll $Repertoire_Plugin

echo 15/$Nombre_Operations
cp /mingw/bin/libtiff-5.dll $Repertoire_Plugin

echo 16/$Nombre_Operations
cp /mingw/bin/pthreadGC2-w32.dll $Repertoire_Plugin

echo 17/$Nombre_Operations
cp /mingw/bin/zlib1.dll $Repertoire_Plugin


echo 18/$Nombre_Operations
cp $Repertoire_Source/gmic_gimp.exe $Repertoire_Plugin




echo 19/$Nombre_Operations
#### cp /mingw/bin/curl.exe $Repertoire_Plugin
cp /mingw/bin/libcurl-4.dll $Repertoire_Plugin

echo 20/$Nombre_Operations
cp /mingw/bin/libssh2-1_.dll $Repertoire_Plugin

echo 21/$Nombre_Operations
cp /mingw/bin/libeay32_.dll $Repertoire_Plugin

echo 22/$Nombre_Operations
cp /mingw/bin/zlib1_.dll $Repertoire_Plugin






echo The plug-in GMIC-GIMP is compiled.
echo Now you have to be very patient because the compilation GMIC starts...





echo 23/$Nombre_Operations
####  /env/gcc492/mingw32/bin/i686-w64-mingw32-g++.exe -o gmic_main.o -c gmic.cpp -fopenmp -Dcimg_use_openmp -Dgmic_build -std=c++11 -I/mingw/include -I/env/gcc492/mingw32/include -I/env/gcc492/mingw32/i686-w64-mingw32/include -pipe -O3 -mms-bitfields -s -march=i686 -Wall -W -Dgmic_is_parallel -Dcimg_display=2 -Dcimg_appname=\"gmic\" -Dcimg_use_zlib -Dcimg_use_png -Dcimg_use_jpeg -Dcimg_use_fftw3 -Dcimg_use_tiff -Dgmic_split_compilation -Dgmic_main -Dgmic_check_image
/env/gcc492/mingw32/bin/i686-w64-mingw32-g++.exe -o gmic_main.o -c gmic.cpp -fopenmp -Dcimg_use_curl -Dcimg_verbosity=3 -g -Dcimg_use_opencv -Dcimg_use_openmp -Dgmic_build -DPSAPI_VERSION=1 $commande_version=$version_gmic -std=c++11 -I/mingw/include -I/env/gcc492/mingw32/include -I/env/gcc492/mingw32/i686-w64-mingw32/include -I/opencv/include -I/opencv/include/opencv -I/opencv/include/opencv2 -pipe -O3 -mms-bitfields -s -march=i686 -Wall -W -Dgmic_is_parallel -Dcimg_display=2 -Dcimg_appname=\"gmic\" -Dcimg_use_zlib -Dcimg_use_png -Dcimg_use_jpeg -Dcimg_use_fftw3 -Dcimg_use_tiff -Dgmic_split_compilation -Dgmic_main -Dgmic_check_image


echo 24/$Nombre_Operations
####  /env/gcc492/mingw32/bin/i686-w64-mingw32-g++.exe -o gmic.exe gmic_main.o -fopenmp -Dcimg_use_openmp -I/mingw/include -I/env/gcc492/mingw32/include -I/env/gcc492/mingw32/i686-w64-mingw32/include -lm -L/env/gcc492/mingw32/lib -L/env/gcc492/mingw32/i686-w64-mingw32/lib -L/mingw/lib -s -march=i686 -lpthread -lm -lgdi32 -lfftw3 -lpng16 -lz -ltiff -ljpeg -lgomp
/env/gcc492/mingw32/bin/i686-w64-mingw32-g++.exe -o gmic.exe gmic_main.o -fopenmp -Dcimg_use_curl -Dcimg_verbosity=3 -g -Dcimg_use_opencv -Dcimg_use_openmp -Dgmic_build -DPSAPI_VERSION=1 $commande_version=$version_gmic -std=c++11 -I/mingw/include -I/env/gcc492/mingw32/include -I/env/gcc492/mingw32/i686-w64-mingw32/include -I/opencv/include -I/opencv/include/opencv -I/opencv/include/opencv2 -lm -L/env/gcc492/mingw32/lib -L/env/gcc492/mingw32/i686-w64-mingw32/lib -L/mingw/lib -s -march=i686 -lpthread -lm -lgdi32 -lfftw3 -lpng16 -lz -ltiff -ljpeg -lgomp -lcurl -lpsapi /opencv/lib/opencv_calib3d2410.lib /opencv/lib/opencv_contrib2410.lib /opencv/lib/opencv_core2410.lib /opencv/lib/opencv_features2d2410.lib /opencv/lib/opencv_flann2410.lib /opencv/lib/opencv_gpu2410.lib /opencv/lib/opencv_highgui2410.lib /opencv/lib/opencv_imgproc2410.lib /opencv/lib/opencv_legacy2410.lib /opencv/lib/opencv_ml2410.lib /opencv/lib/opencv_nonfree2410.lib /opencv/lib/opencv_objdetect2410.lib /opencv/lib/opencv_ocl2410.lib /opencv/lib/opencv_photo2410.lib /opencv/lib/opencv_stitching2410.lib /opencv/lib/opencv_superres2410.lib /opencv/lib/opencv_video2410.lib /opencv/lib/opencv_videostab2410.lib

echo 25/$Nombre_Operations
/env/gcc492/mingw32/bin/strip.exe gmic.exe

echo 26/$Nombre_Operations
####  /env/gcc492/mingw32/bin/i686-w64-mingw32-g++.exe -o gmic-silent.exe gmic_main.o -fopenmp -Dcimg_use_openmp -I/mingw/include -I/env/gcc492/mingw32/include -I/env/gcc492/mingw32/i686-w64-mingw32/include -lm -L/env/gcc492/mingw32/lib -L/env/gcc492/mingw32/i686-w64-mingw32/lib -L/mingw/lib -s -march=i686 -mwindows -lpthread -lm -lgdi32 -lfftw3 -lpng16 -lz -ltiff -ljpeg -lgomp
/env/gcc492/mingw32/bin/i686-w64-mingw32-g++.exe -o gmic-silent.exe gmic_main.o -Dcimg_use_curl -Dcimg_verbosity=3 -g -fopenmp -Dcimg_use_opencv -Dcimg_use_openmp -Dgmic_build -DPSAPI_VERSION=1 $commande_version=$version_gmic -std=c++11 -I/mingw/include -I/env/gcc492/mingw32/include -I/env/gcc492/mingw32/i686-w64-mingw32/include -I/opencv/include -I/opencv/include/opencv -I/opencv/include/opencv2 -lm -L/env/gcc492/mingw32/lib -L/env/gcc492/mingw32/i686-w64-mingw32/lib -L/mingw/lib -s -march=i686 -mwindows -lpthread -lm -lgdi32 -lfftw3 -lpng16 -lz -ltiff -ljpeg -lgomp -lcurl -lpsapi /opencv/lib/opencv_calib3d2410.lib /opencv/lib/opencv_contrib2410.lib /opencv/lib/opencv_core2410.lib /opencv/lib/opencv_features2d2410.lib /opencv/lib/opencv_flann2410.lib /opencv/lib/opencv_gpu2410.lib /opencv/lib/opencv_highgui2410.lib /opencv/lib/opencv_imgproc2410.lib /opencv/lib/opencv_legacy2410.lib /opencv/lib/opencv_ml2410.lib /opencv/lib/opencv_nonfree2410.lib /opencv/lib/opencv_objdetect2410.lib /opencv/lib/opencv_ocl2410.lib /opencv/lib/opencv_photo2410.lib /opencv/lib/opencv_stitching2410.lib /opencv/lib/opencv_superres2410.lib /opencv/lib/opencv_video2410.lib /opencv/lib/opencv_videostab2410.lib

echo 27/$Nombre_Operations
/env/gcc492/mingw32/bin/strip.exe gmic-silent.exe


####																																																																																																																																																																																																																																																				


####GMICOL

echo 28/$Nombre_Operations
/env/gcc492/mingw32/bin/i686-w64-mingw32-g++.exe -o gmicol.o -c gmic.cpp -fopenmp -Dcimg_use_curl -Dcimg_verbosity=3 -g -Dcimg_use_opencv -Dcimg_use_openmp -Dgmic_build -DPSAPI_VERSION=1 $commande_version=$version_gmic -std=c++11 -I/mingw/include -I/env/gcc492/mingw32/include -I/env/gcc492/mingw32/i686-w64-mingw32/include -I/opencv/include -I/opencv/include/opencv -I/opencv/include/opencv2 -pipe -O3 -mms-bitfields -s -march=i686 -Wall -W -Dgmic_is_parallel -Dcimg_display=0 -Dcimg_appname=\"gmic\" -Dcimg_use_zlib -Dcimg_use_png -Dcimg_use_jpeg -Dcimg_use_fftw3 -Dcimg_use_tiff -Dgmic_split_compilation -Dgmic_main -Dgmic_check_image

echo 29/$Nombre_Operations
/env/gcc492/mingw32/bin/i686-w64-mingw32-g++.exe -o gmicol.exe gmicol.o -fopenmp -Dcimg_use_curl -Dcimg_verbosity=3 -g -Dcimg_use_opencv -Dcimg_use_openmp -Dgmic_build -DPSAPI_VERSION=1 $commande_version=$version_gmic -std=c++11 -I/mingw/include -I/env/gcc492/mingw32/include -I/env/gcc492/mingw32/i686-w64-mingw32/include -I/opencv/include -I/opencv/include/opencv -I/opencv/include/opencv2 -lm -L/env/gcc492/mingw32/lib -L/env/gcc492/mingw32/i686-w64-mingw32/lib -L/mingw/lib -s -march=i686 -lpthread -lm -lgdi32 -lfftw3 -lpng16 -lz -ltiff -ljpeg -lgomp -lcurl -lpsapi /opencv/lib/opencv_calib3d2410.lib /opencv/lib/opencv_contrib2410.lib /opencv/lib/opencv_core2410.lib /opencv/lib/opencv_features2d2410.lib /opencv/lib/opencv_flann2410.lib /opencv/lib/opencv_gpu2410.lib /opencv/lib/opencv_highgui2410.lib /opencv/lib/opencv_imgproc2410.lib /opencv/lib/opencv_legacy2410.lib /opencv/lib/opencv_ml2410.lib /opencv/lib/opencv_nonfree2410.lib /opencv/lib/opencv_objdetect2410.lib /opencv/lib/opencv_ocl2410.lib /opencv/lib/opencv_photo2410.lib /opencv/lib/opencv_stitching2410.lib /opencv/lib/opencv_superres2410.lib /opencv/lib/opencv_video2410.lib /opencv/lib/opencv_videostab2410.lib

echo 30/$Nombre_Operations
/env/gcc492/mingw32/bin/strip.exe gmicol.exe

echo 31/$Nombre_Operations
/env/gcc492/mingw32/bin/i686-w64-mingw32-g++.exe -o gmicol-silent.exe gmicol.o -Dcimg_use_curl -Dcimg_verbosity=3 -g -fopenmp -Dcimg_use_opencv -Dcimg_use_openmp -Dgmic_build -DPSAPI_VERSION=1 $commande_version=$version_gmic -std=c++11 -I/mingw/include -I/env/gcc492/mingw32/include -I/env/gcc492/mingw32/i686-w64-mingw32/include -I/opencv/include -I/opencv/include/opencv -I/opencv/include/opencv2 -lm -L/env/gcc492/mingw32/lib -L/env/gcc492/mingw32/i686-w64-mingw32/lib -L/mingw/lib -s -march=i686 -mwindows -lpthread -lm -lgdi32 -lfftw3 -lpng16 -lz -ltiff -ljpeg -lgomp -lcurl -lpsapi /opencv/lib/opencv_calib3d2410.lib /opencv/lib/opencv_contrib2410.lib /opencv/lib/opencv_core2410.lib /opencv/lib/opencv_features2d2410.lib /opencv/lib/opencv_flann2410.lib /opencv/lib/opencv_gpu2410.lib /opencv/lib/opencv_highgui2410.lib /opencv/lib/opencv_imgproc2410.lib /opencv/lib/opencv_legacy2410.lib /opencv/lib/opencv_ml2410.lib /opencv/lib/opencv_nonfree2410.lib /opencv/lib/opencv_objdetect2410.lib /opencv/lib/opencv_ocl2410.lib /opencv/lib/opencv_photo2410.lib /opencv/lib/opencv_stitching2410.lib /opencv/lib/opencv_superres2410.lib /opencv/lib/opencv_video2410.lib /opencv/lib/opencv_videostab2410.lib

echo 32/$Nombre_Operations
/env/gcc492/mingw32/bin/strip.exe gmicol-silent.exe





echo 33/$Nombre_Operations
rm -f -r $Repertoire_GMIC

echo 34/$Nombre_Operations
mkdir $Repertoire_GMIC


echo 35/$Nombre_Operations
cp /env/gcc492/mingw32/bin/libgomp-1.dll $Repertoire_GMIC

echo 36/$Nombre_Operations
cp /mingw/bin/libfftw3-3.dll $Repertoire_GMIC

echo 37/$Nombre_Operations
cp /env/gcc492/mingw32/bin/libgcc_s_dw2-1.dll $Repertoire_GMIC

echo 38/$Nombre_Operations
cp /env/gcc492/mingw32/bin/libwinpthread-1.dll $Repertoire_GMIC

echo 39/$Nombre_Operations
cp /mingw/bin/libjpeg-9.dll $Repertoire_GMIC

echo 40/$Nombre_Operations
cp /mingw/bin/liblzma-5.dll $Repertoire_GMIC

echo 41/$Nombre_Operations
cp /mingw/bin/libpng16-16.dll $Repertoire_GMIC

echo 42/$Nombre_Operations
cp /env/gcc492/mingw32/bin/libstdc++-6.dll $Repertoire_GMIC

echo 43/$Nombre_Operations
cp /mingw/bin/libtiff-5.dll $Repertoire_GMIC

echo 44/$Nombre_Operations
cp /mingw/bin/pthreadGC2-w32.dll $Repertoire_GMIC

echo 45/$Nombre_Operations
cp /mingw/bin/zlib1.dll $Repertoire_GMIC



echo 46/$Nombre_Operations
cp /mingw/bin/libwinpthread-1.dll $Repertoire_GMIC





echo 47/$Nombre_Operations
#### cp /mingw/Preferences/old-plug-ins/_gmic/curl.exe $Repertoire_GMIC
cp /mingw/bin/libcurl-4.dll $Repertoire_GMIC

echo 48/$Nombre_Operations
cp /mingw/bin/libssh2-1_.dll $Repertoire_GMIC

echo 49/$Nombre_Operations
cp /mingw/bin/libeay32_.dll $Repertoire_GMIC

echo 50/$Nombre_Operations
cp /mingw/bin/zlib1_.dll $Repertoire_GMIC





#### OpenCV

#### Les 6 DLL pour G'MIC/OpenCV 32 bits Windows
#### opencv_core2410.dll
#### opencv_highgui2410.dll
#### opencv_ffmpeg2410.dll
#### libgcc_s_dw2-1.dll (non fournie dans le paquet OpenCV de sourceforge! dispo sur http://www.aljacom.com/~gmic/GMIC-32bit-WIN-OPENCV-20141201.7z   Volume : 18 485 375 octets ou, peut-être (selon la version), dans le répertoire du compilateur GCC)
#### msvcp120.dll  (non fournie dans le paquet OpenCV de sourceforge) Visual C++ Redistributable Packages for Visual Studio 2013 Win32
#### msvcr120.dll  (non fournie dans le paquet OpenCV de sourceforge) Visual C++ Redistributable Packages for Visual Studio 2013 Win32

echo 51/$Nombre_Operations
cp /opencv/bin/opencv_core2410.dll $Repertoire_GMIC

echo 52/$Nombre_Operations
cp /opencv/bin/opencv_highgui2410.dll $Repertoire_GMIC

echo 53/$Nombre_Operations
cp /opencv/bin/opencv_ffmpeg2410.dll $Repertoire_GMIC

echo 54/$Nombre_Operations
cp /opencv/Visual_C++_Redistributable_Packages_for_Visual_Studio_2013_Win32/msvcp120.dll $Repertoire_GMIC

echo 55/$Nombre_Operations
cp /opencv/Visual_C++_Redistributable_Packages_for_Visual_Studio_2013_Win32/msvcr120.dll $Repertoire_GMIC





echo 56/$Nombre_Operations
cp $Repertoire_Source/gmic.exe $Repertoire_GMIC

echo 57/$Nombre_Operations
cp $Repertoire_Source/gmic-silent.exe $Repertoire_GMIC


####GMICOL
echo 58/$Nombre_Operations
cp $Repertoire_Source/gmicol.exe $Repertoire_GMIC

echo 59/$Nombre_Operations
cp $Repertoire_Source/gmicol-silent.exe $Repertoire_GMIC



echo 60/$Nombre_Operations
rm -f $Repertoire_Source/Start_Terminal_With_Test_GMIC.bat

echo 61/$Nombre_Operations
echo -e "cmd /T:0f /E:ON /K \"prompt $G&&cls&&gmic -verbose - 256,256,1,4 -gimp_chessboard 32,32,0,0,0,1,0,0,0,255,255,255,255,255 -window -1,-1,0,-1,TEST -wait 500&&echo Current Directory = %CD%&&echo You can type or paste a command recognized by GMIC&&echo For example :    gmic 256,256,1,4 -gimp_chessboard 32,32,0,0,0,1,0,0,0,255,255,255,255,255\"\n" > Start_Terminal_With_Test_GMIC.bat

echo 62/$Nombre_Operations
cp $Repertoire_Source/Start_Terminal_With_Test_GMIC.bat $Repertoire_GMIC

echo 63/$Nombre_Operations
rm -f $Repertoire_Source/Start_Terminal_With_Test_GMIC.bat

echo GMIC is compiled.
echo Creating the  gmic_gmic-gimp_win32.tar.xz  archive...

echo 64/$Nombre_Operations
rm -f /env/gmic_gmic-gimp_win32.tar.xz

echo 65/$Nombre_Operations
/usr/bin/tar.exe -cf /env/gmic_gmic-gimp_win32.tar /env/GMIC-32bit-WIN /env/GMIC-GIMP-PLUGIN-32bit-WIN

echo 66/$Nombre_Operations
/usr/bin/xz.exe -ze /env/gmic_gmic-gimp_win32.tar


echo FIN - END