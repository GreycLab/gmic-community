
#############################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################
####
####
#### Script "compile_gmic_and_gmic-gimp_plugin_64_win.sh" pour compiler GMIC et le plugin G'MIC pour Gimp avec les sources de SourceForge 
#### Ce script est très simple :
####	- Il compile le plug-in.
####	- Il crée l'environnement complet du greffon dans le répertoire GMIC-GIMP-PLUGIN-64bit-WIN (en écrasant le répertoire existant).
####	- Il crée l'environnement complet de GMIC dans le répertoire GMIC-64bit-WIN (en écrasant le répertoire existant).
####	- Il crée l'archive gmic_gmic-gimp_win64.tar.xz 
#### 
#### Ce script "compile_gmic_and_gmic-gimp_plugin_64_win.sh" fonctionne avec l'environnement de compilation 64 bits Windows disponible sur : http://www.aljacom.com/~gimp/petit-msys-mingw-64bits-gimp28.7z
#### Il faut l'installer dans "C:\petit-msys-mingw-64bits-gimp28".
#### Ce srcipt utilise GCC 4.9.2 qui doit être installé dans le répertoire "C:\petit-msys-mingw-64bits-gimp28" . Il faut obtenir "C:\petit-msys-mingw-64bits-gimp28\gcc492\mingw64\bin\x86_64-w64-mingw32-g++.exe"
####
#### Utilisation :
####    - Vérifier la valeur de la variable "Repertoire_Source" de ce fichier.
####    - Éditer ce fichier et modifier les variables : Stable="yes"  ou   Stable="no"  et  version_gmic=\"samj_20150414\"
####	- Démarrer MSYS en cliquant sur "start_MSYS_GCC492.bat".
####	- Entrer les deux lignes de commandes qui suivent.
####			cd /env
####			./compile_gmic_and_gmic-gimp_plugin_64_win.sh
####	- Il y a 67 opérations à effectuer. Attendre le message "FIN - END".
####	- L'ensemple pour faire fonctionner le plug-in est disponible dans le répertoire "GMIC-GIMP-PLUGIN-64bit-WIN" ( C:\petit-msys-mingw-64bits-gimp28\GMIC-GIMP-PLUGIN-64bit-WIN ).
####	- L'ensemple pour faire fonctionner GMIC disponible dans le répertoire "GMIC-64bit-WIN" ( C:\petit-msys-mingw-64bits-gimp28\GMIC-64bit-WIN ).
####
####
#### _______________________________________________________________________________________________________________________________________________________________________________________________
####
#### English translation
####
#### Script "compile_gmic_and_gmic-gimp_plugin_64_win.sh" to compile GMIC and the plugin G'MIC for Gimp with sources from SourceForge
#### This script is very simple:
####	- It compiles the plugin.
####	- It creates the entire environment for the plug-in in the "GMIC-GIMP-PLUGIN-64bit-WIN" directory (overwriting the existing directory)
####	- It creates the archive gmic_gmic-gimp_win64.tar.xz 
####
#### This script "compile_gmic_and_gmic-gimp_plugin_64_win.sh" works with 64-bit build environment for Windows available :  http://www.aljacom.com/~gimp/petit-msys-mingw-64bits-gimp28.7z
#### It must be installed in "C:\petit-msys-mingw-64bits-gimp28".
#### This srcipt using GCC 4.9.2 to be installed in the directory "C:\petit-msys-mingw-64bits-gimp28" . Must be obtained "C:\petit-msys-mingw-64bits-gimp28\gcc492\mingw64\bin\x86_64-w64-mingw32-g++.exe"
####
#### Use:
####    - Check the value of the variable "Repertoire_Source" in this file.
####    - Edit this file, set correct values of the variables : Stable="yes"  or   Stable="no"  and  version_gmic=\"samj_20150414\"
####	- Start MSYS clicking "start_MSYS_GCC492.bat".
####	- Enter the two command lines that follow.
####			cd /env
####			./compile_gmic_and_gmic-gimp_plugin_64_win.sh
####	- There are 67 operations to be performed. Wait for the message "FIN - END".
####	- The plug-in is available in the "GMIC-GIMP-PLUGIN-64bit-WIN" directory ( C:\petit-msys-mingw-64bits-gimp28\GMIC-GIMP-PLUGIN-64bit-WIN ).
####	- GMIC is available in the "GMIC-64bit-WIN" directory ( C:\petit-msys-mingw-64bits-gimp28\GMIC-64bit-WIN ).
####
####
####
#### version 17  20150524  par samj le 24 mai 2015       g_g_wau.exe supprimé
#### version 16  20150417  par samj le 17 avril 2015     Ajout compilation g_g_wau.cpp > g_g_wau.exe > /Without_Auto_Update/gmic_gimp.exe
#### version 15  20150414  par samj le 14 avril 2015     Ajouts -Dgmic_gimp  $commande_version=$version_gmic - Ajouts variables   Stable="yes"  ou   Stable="no"  et  version_gmic=\"samj_20150414\"
#### version 14  20150405  par samj le 5 avril 2015      Pâques, ajouts -DPSAPI_VERSION=1 et -lpsapi et -std=c++11 pour le plug-in ( https://msdn.microsoft.com/en-us/library/windows/desktop/ms682050(v=vs.85).aspx )
#### version 13  20150228  par samj le 28 février 2015   gcc 4.9.2 
#### version 12  20150219  par samj le 19 février 2015   Ajout pour G'MIC en lignes de commandes et Gimp plug-in -Dcimg_use_curl -lcurl . L'exécutable curl.exe est supprimé.
#### version 11  20150208  par samj le 8 février 2015    Ajout gmicol
#### version 10  20141202  par samj le 2 décembre 2014   Ajout -Dcimg_verbosity=3 -g
#### version 9   20141201  par samj le 1 décembre 2014   Modifications pour G'MIC 1.6.0.3 beta Ajouts OpenCV
#### version 8   20141013  par samj le 13 octobre 2014   Modifications pour G'MIC 1.6.0.2 beta . Modification de -Dcimg_display pour le plug-in.
#### version 7   20140822  par samj le 22 août 2014      Modifications pour G'MIC 1.6.0.1 . Ajouts -Dgmic_main -lgomp -std=c++11 . Supprimer : GIT , -Dgmic_float_only pour plug-in , compilation des fichiers gmic_bool.o gmic_uchar.o gmic_char.o gmic_ushort.o gmic_short.o gmic_uint.o gmic_int.o gmic_ulong.o gmic_long.o gmic_float.o gmic_double.o
#### version 6   20140702  par samj le 2 juillet 2014    Ajouts gmic_ulong.o gmic_long.o
#### version 5   20140616  par samj le 16 juin 2014      supprimer -Dgmic_use_openmp
#### version 4   20140610  par samj le 10 juin 2014      gcc 4.9.0 
#### version 3   20140608  par samj le 8 juin 2014       Ajouts -fopenmp -Dcimg_use_openmp libgomp-1.dll libwinpthread-1.dll
#### version 2   20140127  par samj le 27 janvier 2014   Ajout -Dgmic_check_image
#### version 1   20131030  par samj le 30 octobre 2013
####
####
####
#############################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################




#### Compilation de GMIC et du plug-in, création de l'archive gmic_gmic-gimp_win64.tar.xz 


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



Nombre_Operations=67
Repertoire_Source=/env/gmic/src
Repertoire_Plugin=/env/GMIC-GIMP-PLUGIN-64bit-WIN
Repertoire_GMIC=/env/GMIC-64bit-WIN


echo 01/$Nombre_Operations
cd $Repertoire_Source

echo 02/$Nombre_Operations
/env/gcc492/mingw64/bin/x86_64-w64-mingw32-g++.exe -o gmic_gimp.o -c gmic.cpp -DPSAPI_VERSION=1 -Dgmic_gimp $commande_version=$version_gmic -fopenmp -Dcimg_use_curl -Dcimg_use_openmp -Dgmic_build -std=c++11 -I/env/gcc492/mingw64/include -I/mingw/include -I/env/gcc492/mingw64/x86_64-w64-mingw32/include -pipe -O3 -mms-bitfields -s -m64 -Wall -W -mtune=generic -Dcimg_use_vt100 -Dgmic_is_parallel -Dcimg_use_fftw3 -Dcimg_use_png -Dcimg_use_zlib -Dcimg_use_tiff -Dcimg_use_jpeg -Dcimg_display=2 -Dcimg_use_rng -Dgmic_gimp -Dgmic_check_image

echo 03/$Nombre_Operations
/env/gcc492/mingw64/bin/x86_64-w64-mingw32-g++.exe -o gmic_gimp.exe gmic_gimp.cpp gmic_gimp.o -DPSAPI_VERSION=1 -Dgmic_gimp $commande_version=$version_gmic -fopenmp -Dcimg_use_curl -Dcimg_use_openmp `gimptool-2.0.exe --cflags` -Dgmic_build -std=c++11 -I/env/gcc492/mingw64/include -I/mingw/include -I/env/gcc492/mingw64/x86_64-w64-mingw32/include -pipe -O3 -mms-bitfields -s -m64 -Wall -W -mtune=generic -Dcimg_use_vt100 -Dgmic_is_parallel -Dcimg_use_fftw3 -Dcimg_use_png -Dcimg_use_zlib -Dcimg_use_tiff -Dcimg_use_jpeg -Dcimg_use_vt100 -Dcimg_display=2 -Dcimg_use_rng -Dgmic_check_image `gimptool-2.0.exe --libs` -L/env/gcc492/mingw64/lib -L/mingw/lib -L/env/gcc492/mingw64/x86_64-w64-mingw32/lib -mwindows -lpthread -lm -lfftw3 -lpng16 -lz -ltiff -ljpeg -lgomp -lcurl -lpsapi

echo 04/$Nombre_Operations
#### temporisation...
/env/gcc492/mingw64/bin/strip.exe -V
/env/gcc492/mingw64/bin/strip.exe gmic_gimp.exe


echo 05/$Nombre_Operations
rm -f -r $Repertoire_Plugin

echo 06/$Nombre_Operations
mkdir $Repertoire_Plugin

echo 07/$Nombre_Operations
cp /env/gcc492/mingw64/bin/libgomp-1.dll $Repertoire_Plugin


echo 08/$Nombre_Operations
cp /env/gcc492/mingw64/bin/libwinpthread-1.dll $Repertoire_Plugin


echo 09/$Nombre_Operations
cp /mingw/bin/libfftw3-3.dll $Repertoire_Plugin

echo 10/$Nombre_Operations
cp /env/gcc492/mingw64/bin/libgcc_s_seh-1.dll $Repertoire_Plugin

echo 11/$Nombre_Operations
cp /mingw/bin/libjpeg-9.dll $Repertoire_Plugin

echo 12/$Nombre_Operations
cp /mingw/bin/liblzma-5__.dll $Repertoire_Plugin

echo 13/$Nombre_Operations
cp /mingw/bin/libpng16-16.dll $Repertoire_Plugin

echo 14/$Nombre_Operations
cp /env/gcc492/mingw64/bin/libstdc++-6.dll $Repertoire_Plugin

echo 15/$Nombre_Operations
cp /mingw/bin/libtiff-5.dll $Repertoire_Plugin

echo 16/$Nombre_Operations
cp /mingw/bin/pthreadGC2-w64.dll $Repertoire_Plugin

echo 17/$Nombre_Operations
cp /mingw/bin/zlib1.dll $Repertoire_Plugin

echo 18/$Nombre_Operations
cp /mingw/bin/zlib1__.dll $Repertoire_Plugin

echo 19/$Nombre_Operations
cp $Repertoire_Source/gmic_gimp.exe $Repertoire_Plugin


echo 20/$Nombre_Operations
cp /mingw/bin/libcurl-4.dll $Repertoire_Plugin

echo 21/$Nombre_Operations
cp /mingw/bin/ssleay32.dll $Repertoire_Plugin


echo 22/$Nombre_Operations
cp /mingw/bin/libeay32.dll $Repertoire_Plugin

echo 23/$Nombre_Operations
cp /mingw/bin/libeay32__.dll $Repertoire_Plugin

echo 24/$Nombre_Operations
cp /mingw/bin/libssh2-1__.dll $Repertoire_Plugin





echo The plug-in GMIC-GIMP is compiled.
echo Now you have to be very patient because the compilation GMIC starts...

echo 25/$Nombre_Operations
/env/gcc492/mingw64/bin/x86_64-w64-mingw32-g++.exe -o gmic_main.o -c gmic.cpp -fopenmp -Dcimg_verbosity=3 -g -Dcimg_use_curl -Dcimg_use_opencv -Dcimg_use_openmp -Dgmic_build -std=c++11 -DPSAPI_VERSION=1 $commande_version=$version_gmic -I/env/gcc492/mingw64/include -I/mingw/include -I/env/gcc492/mingw64/x86_64-w64-mingw32/include -I/opencv/include -I/opencv/include/opencv -I/opencv/include/opencv2 -pipe -O3 -mms-bitfields -s -m64 -Wall -W -Dgmic_is_parallel -Dcimg_display=2 -Dcimg_appname=\"gmic\" -Dcimg_use_zlib -Dcimg_use_png -Dcimg_use_jpeg -Dcimg_use_fftw3 -Dcimg_use_tiff -Dgmic_split_compilation -Dgmic_main -Dgmic_check_image

echo 26/$Nombre_Operations
/env/gcc492/mingw64/bin/x86_64-w64-mingw32-g++.exe -o gmic.exe gmic_main.o -fopenmp -Dcimg_verbosity=3 -g -Dcimg_use_curl -Dcimg_use_opencv -Dcimg_use_openmp -Dgmic_build -std=c++11 -DPSAPI_VERSION=1 $commande_version=$version_gmic -I/env/gcc492/mingw64/include -I/mingw/include -I/env/gcc492/mingw64/x86_64-w64-mingw32/include -I/opencv/include -I/opencv/include/opencv -I/opencv/include/opencv2 -lm -L/env/gcc492/mingw64/lib -L/mingw/lib -L/env/gcc492/mingw64/x86_64-w64-mingw32/lib -L/opencv/x64/mingw/lib -m64 -lpthread -lm -lgdi32 -lfftw3 -lpng16 -lz -ltiff -ljpeg -lgomp -lcurl -lpsapi -s -lopencv_imgproc2410.dll -lopencv_core2410.dll -lopencv_highgui2410.dll /opencv/x64/mingw/lib/libopencv_calib3d2410.dll.a /opencv/x64/mingw/lib/libopencv_contrib2410.dll.a /opencv/x64/mingw/lib/libopencv_core2410.dll.a /opencv/x64/mingw/lib/libopencv_features2d2410.dll.a /opencv/x64/mingw/lib/libopencv_flann2410.dll.a /opencv/x64/mingw/lib/libopencv_gpu2410.dll.a /opencv/x64/mingw/lib/libopencv_highgui2410.dll.a /opencv/x64/mingw/lib/libopencv_imgproc2410.dll.a /opencv/x64/mingw/lib/libopencv_legacy2410.dll.a /opencv/x64/mingw/lib/libopencv_ml2410.dll.a /opencv/x64/mingw/lib/libopencv_nonfree2410.dll.a /opencv/x64/mingw/lib/libopencv_objdetect2410.dll.a /opencv/x64/mingw/lib/libopencv_ocl2410.dll.a /opencv/x64/mingw/lib/libopencv_photo2410.dll.a /opencv/x64/mingw/lib/libopencv_stitching2410.dll.a /opencv/x64/mingw/lib/libopencv_superres2410.dll.a /opencv/x64/mingw/lib/libopencv_video2410.dll.a /opencv/x64/mingw/lib/libopencv_videostab2410.dll.a

echo 27/$Nombre_Operations
/env/gcc492/mingw64/bin/strip.exe gmic.exe

echo 28/$Nombre_Operations
/env/gcc492/mingw64/bin/x86_64-w64-mingw32-g++.exe -o gmic-silent.exe gmic_main.o -fopenmp -Dcimg_verbosity=3 -g -Dcimg_use_curl -Dcimg_use_opencv -Dcimg_use_openmp -Dgmic_build -std=c++11 -DPSAPI_VERSION=1 $commande_version=$version_gmic -I/env/gcc492/mingw64/include -I/mingw/include -I/env/gcc492/mingw64/x86_64-w64-mingw32/include -I/opencv/include -I/opencv/include/opencv -I/opencv/include/opencv2 -lm -L/env/gcc492/mingw64/lib -L/mingw/lib -L/env/gcc492/mingw64/x86_64-w64-mingw32/lib -L/opencv/x64/mingw/lib -m64 -lpthread -mwindows -lm -lgdi32 -lfftw3 -lpng16 -lz -ltiff -ljpeg -lgomp -lcurl -lpsapi -s -lopencv_imgproc2410.dll -lopencv_core2410.dll -lopencv_highgui2410.dll /opencv/x64/mingw/lib/libopencv_calib3d2410.dll.a /opencv/x64/mingw/lib/libopencv_contrib2410.dll.a /opencv/x64/mingw/lib/libopencv_core2410.dll.a /opencv/x64/mingw/lib/libopencv_features2d2410.dll.a /opencv/x64/mingw/lib/libopencv_flann2410.dll.a /opencv/x64/mingw/lib/libopencv_gpu2410.dll.a /opencv/x64/mingw/lib/libopencv_highgui2410.dll.a /opencv/x64/mingw/lib/libopencv_imgproc2410.dll.a /opencv/x64/mingw/lib/libopencv_legacy2410.dll.a /opencv/x64/mingw/lib/libopencv_ml2410.dll.a /opencv/x64/mingw/lib/libopencv_nonfree2410.dll.a /opencv/x64/mingw/lib/libopencv_objdetect2410.dll.a /opencv/x64/mingw/lib/libopencv_ocl2410.dll.a /opencv/x64/mingw/lib/libopencv_photo2410.dll.a /opencv/x64/mingw/lib/libopencv_stitching2410.dll.a /opencv/x64/mingw/lib/libopencv_superres2410.dll.a /opencv/x64/mingw/lib/libopencv_video2410.dll.a /opencv/x64/mingw/lib/libopencv_videostab2410.dll.a

echo 29/$Nombre_Operations
/env/gcc492/mingw64/bin/strip.exe gmic-silent.exe


####																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																

####GMICOL

echo 30/$Nombre_Operations
/env/gcc492/mingw64/bin/x86_64-w64-mingw32-g++.exe -o gmicol.o -c gmic.cpp -fopenmp -Dcimg_verbosity=3 -g -Dcimg_use_curl -Dcimg_use_opencv -Dcimg_use_openmp -Dgmic_build -std=c++11 -DPSAPI_VERSION=1 $commande_version=$version_gmic -I/env/gcc492/mingw64/include -I/mingw/include -I/env/gcc492/mingw64/x86_64-w64-mingw32/include -I/opencv/include -I/opencv/include/opencv -I/opencv/include/opencv2 -pipe -O3 -mms-bitfields -s -m64 -Wall -W -Dgmic_is_parallel -Dcimg_display=0 -Dcimg_appname=\"gmic\" -Dcimg_use_zlib -Dcimg_use_png -Dcimg_use_jpeg -Dcimg_use_fftw3 -Dcimg_use_tiff -Dgmic_split_compilation -Dgmic_main -Dgmic_check_image

echo 31/$Nombre_Operations
/env/gcc492/mingw64/bin/x86_64-w64-mingw32-g++.exe -o gmicol.exe gmicol.o -fopenmp -Dcimg_verbosity=3 -g -Dcimg_use_curl -Dcimg_use_opencv -Dcimg_use_openmp -Dgmic_build -std=c++11 -DPSAPI_VERSION=1 $commande_version=$version_gmic -I/env/gcc492/mingw64/include -I/mingw/include -I/env/gcc492/mingw64/x86_64-w64-mingw32/include -I/opencv/include -I/opencv/include/opencv -I/opencv/include/opencv2 -lm -L/env/gcc492/mingw64/lib -L/mingw/lib -L/env/gcc492/mingw64/x86_64-w64-mingw32/lib -L/opencv/x64/mingw/lib -m64 -lpthread -lm -lgdi32 -lfftw3 -lpng16 -lz -ltiff -ljpeg -lgomp -lcurl -lpsapi -s -lopencv_imgproc2410.dll -lopencv_core2410.dll -lopencv_highgui2410.dll /opencv/x64/mingw/lib/libopencv_calib3d2410.dll.a /opencv/x64/mingw/lib/libopencv_contrib2410.dll.a /opencv/x64/mingw/lib/libopencv_core2410.dll.a /opencv/x64/mingw/lib/libopencv_features2d2410.dll.a /opencv/x64/mingw/lib/libopencv_flann2410.dll.a /opencv/x64/mingw/lib/libopencv_gpu2410.dll.a /opencv/x64/mingw/lib/libopencv_highgui2410.dll.a /opencv/x64/mingw/lib/libopencv_imgproc2410.dll.a /opencv/x64/mingw/lib/libopencv_legacy2410.dll.a /opencv/x64/mingw/lib/libopencv_ml2410.dll.a /opencv/x64/mingw/lib/libopencv_nonfree2410.dll.a /opencv/x64/mingw/lib/libopencv_objdetect2410.dll.a /opencv/x64/mingw/lib/libopencv_ocl2410.dll.a /opencv/x64/mingw/lib/libopencv_photo2410.dll.a /opencv/x64/mingw/lib/libopencv_stitching2410.dll.a /opencv/x64/mingw/lib/libopencv_superres2410.dll.a /opencv/x64/mingw/lib/libopencv_video2410.dll.a /opencv/x64/mingw/lib/libopencv_videostab2410.dll.a

echo 32/$Nombre_Operations
/env/gcc492/mingw64/bin/strip.exe gmicol.exe

echo 33/$Nombre_Operations
/env/gcc492/mingw64/bin/x86_64-w64-mingw32-g++.exe -o gmicol-silent.exe gmicol.o -fopenmp -Dcimg_verbosity=3 -g -Dcimg_use_curl -Dcimg_use_opencv -Dcimg_use_openmp -Dgmic_build -DPSAPI_VERSION=1 $commande_version=$version_gmic -std=c++11 -I/env/gcc492/mingw64/include -I/mingw/include -I/env/gcc492/mingw64/x86_64-w64-mingw32/include -I/opencv/include -I/opencv/include/opencv -I/opencv/include/opencv2 -lm -L/env/gcc492/mingw64/lib -L/mingw/lib -L/env/gcc492/mingw64/x86_64-w64-mingw32/lib -L/opencv/x64/mingw/lib -m64 -lpthread -mwindows -lm -lgdi32 -lfftw3 -lpng16 -lz -ltiff -ljpeg -lgomp -lcurl -lpsapi -s -lopencv_imgproc2410.dll -lopencv_core2410.dll -lopencv_highgui2410.dll /opencv/x64/mingw/lib/libopencv_calib3d2410.dll.a /opencv/x64/mingw/lib/libopencv_contrib2410.dll.a /opencv/x64/mingw/lib/libopencv_core2410.dll.a /opencv/x64/mingw/lib/libopencv_features2d2410.dll.a /opencv/x64/mingw/lib/libopencv_flann2410.dll.a /opencv/x64/mingw/lib/libopencv_gpu2410.dll.a /opencv/x64/mingw/lib/libopencv_highgui2410.dll.a /opencv/x64/mingw/lib/libopencv_imgproc2410.dll.a /opencv/x64/mingw/lib/libopencv_legacy2410.dll.a /opencv/x64/mingw/lib/libopencv_ml2410.dll.a /opencv/x64/mingw/lib/libopencv_nonfree2410.dll.a /opencv/x64/mingw/lib/libopencv_objdetect2410.dll.a /opencv/x64/mingw/lib/libopencv_ocl2410.dll.a /opencv/x64/mingw/lib/libopencv_photo2410.dll.a /opencv/x64/mingw/lib/libopencv_stitching2410.dll.a /opencv/x64/mingw/lib/libopencv_superres2410.dll.a /opencv/x64/mingw/lib/libopencv_video2410.dll.a /opencv/x64/mingw/lib/libopencv_videostab2410.dll.a

echo 34/$Nombre_Operations
/env/gcc492/mingw64/bin/strip.exe gmicol-silent.exe









echo 35/$Nombre_Operations
rm -f -r $Repertoire_GMIC

echo 36/$Nombre_Operations
mkdir $Repertoire_GMIC

echo 37/$Nombre_Operations
cp /env/gcc492/mingw64/bin/libgomp-1.dll $Repertoire_GMIC

echo 38/$Nombre_Operations
cp /mingw/bin/libfftw3-3.dll $Repertoire_GMIC

echo 39/$Nombre_Operations
cp /env/gcc492/mingw64/bin/libgcc_s_seh-1.dll $Repertoire_GMIC

echo 40/$Nombre_Operations
cp /mingw/bin/libjpeg-9.dll $Repertoire_GMIC

echo 41/$Nombre_Operations
cp /mingw/bin/liblzma-5__.dll $Repertoire_GMIC

echo 42/$Nombre_Operations
cp /mingw/bin/libpng16-16.dll $Repertoire_GMIC

echo 43/$Nombre_Operations
cp /env/gcc492/mingw64/bin/libstdc++-6.dll $Repertoire_GMIC

echo 44/$Nombre_Operations
cp /env/gcc492/mingw64/bin/libwinpthread-1.dll $Repertoire_GMIC

echo 45/$Nombre_Operations
cp /mingw/bin/libtiff-5.dll $Repertoire_GMIC

echo 46/$Nombre_Operations
cp /mingw/bin/pthreadGC2-w64.dll $Repertoire_GMIC

echo 47/$Nombre_Operations
cp /mingw/bin/zlib1.dll $Repertoire_GMIC

echo 48/$Nombre_Operations
cp /mingw/bin/zlib1__.dll $Repertoire_GMIC

echo 49/$Nombre_Operations
cp $Repertoire_Source/gmic.exe $Repertoire_GMIC

echo 50/$Nombre_Operations
cp $Repertoire_Source/gmic-silent.exe $Repertoire_GMIC



echo 51/$Nombre_Operations
cp /mingw/bin/libcurl-4.dll $Repertoire_GMIC

echo 52/$Nombre_Operations
cp /mingw/bin/ssleay32.dll $Repertoire_GMIC


echo 53/$Nombre_Operations
cp /mingw/bin/libeay32.dll $Repertoire_GMIC

echo 54/$Nombre_Operations
cp /mingw/bin/libeay32__.dll $Repertoire_GMIC

echo 55/$Nombre_Operations
cp /mingw/bin/libssh2-1__.dll $Repertoire_GMIC






####GMICOL
echo 56/$Nombre_Operations
cp $Repertoire_Source/gmicol.exe $Repertoire_GMIC

echo 57/$Nombre_Operations
cp $Repertoire_Source/gmicol-silent.exe $Repertoire_GMIC







#### OpenCV
echo 58/$Nombre_Operations
cp /opencv/x64/mingw/bin/libopencv_core2410.dll $Repertoire_GMIC

echo 59/$Nombre_Operations
cp /opencv/x64/mingw/bin/libopencv_highgui2410.dll $Repertoire_GMIC

echo 60/$Nombre_Operations
cp /opencv/x64/mingw/bin/opencv_ffmpeg2410_64.dll $Repertoire_GMIC


echo 61/$Nombre_Operations
rm -f $Repertoire_Source/Start_Terminal_With_Test_GMIC.bat

echo 62/$Nombre_Operations
echo -e "cmd /T:0f /E:ON /K \"prompt $G&&cls&&gmic -verbose - 256,256,1,4 -gimp_chessboard 32,32,0,0,0,1,0,0,0,255,255,255,255,255 -window -1,-1,0,-1,TEST -wait 500&&echo Current Directory = %CD%&&echo You can type or paste a command recognized by GMIC&&echo For example :    gmic 256,256,1,4 -gimp_chessboard 32,32,0,0,0,1,0,0,0,255,255,255,255,255\"\n" > Start_Terminal_With_Test_GMIC.bat

echo 63/$Nombre_Operations
cp $Repertoire_Source/Start_Terminal_With_Test_GMIC.bat $Repertoire_GMIC

echo 64/$Nombre_Operations
rm -f $Repertoire_Source/Start_Terminal_With_Test_GMIC.bat

echo GMIC is compiled.
echo Creating the  gmic_gmic-gimp_win64.tar.xz  archive...

echo 65/$Nombre_Operations
rm -f /env/gmic_gmic-gimp_win64.tar.xz

echo 66/$Nombre_Operations
/usr/bin/tar.exe -cf /env/gmic_gmic-gimp_win64.tar /env/GMIC-64bit-WIN /env/GMIC-GIMP-PLUGIN-64bit-WIN

echo 67/$Nombre_Operations
/usr/bin/xz.exe -ze /env/gmic_gmic-gimp_win64.tar


echo FIN - END