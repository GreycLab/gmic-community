
#############################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################
####
####
#### Script "compile_gmic_and_gmic-gimp_plugin_32_win_OPENCV.sh" pour compiler GMIC et le plugin G'MIC.
#### Ce script est très simple :
####	- Il compile le plug-in.
####	- Il crée l'environnement complet du greffon dans le répertoire GMIC-GIMP-PLUGIN-32bit-WIN (en écrasant le répertoire existant).
####	- Il crée l'environnement complet de GMIC dans le répertoire GMIC-32bit-WIN (en écrasant le répertoire existant).
####	- Il crée l'archive gmic_gmic-gimp_win32.tar.xz 
#### 
#### Ce script "compile_gmic_and_gmic-gimp_plugin_32_win_OPENCV.sh" fonctionne avec l'environnement de compilation Windows utilisant MSYS2 disponible sur : http://www.aljacom.com/~gimp
#### Il faut l'installer dans "C:\petit-msys2-mingw-32bits-64bits-gimp28".
#### Ce srcipt utilise GCC 4.9.2 qui doit être installé dans le répertoire "C:\petit-msys2-mingw-32bits-64bits-gimp28" .
####
#### Utilisation :
####	- Démarrer MSYS en cliquant sur "start_MSYS2_GCC492-32bit.bat".
####    - Éditer ce fichier et modifier les variables : Stable="yes"  ou   Stable="no"  et  version_gmic=\"samj_20150414\"
####	- Entrer les deux lignes de commandes qui suivent.
####			cd /env
####			./compile_gmic_and_gmic-gimp_plugin_32_win.sh
####	- Il y a 87 opérations à effectuer. Attendre le message "FIN - END".
####	- L'ensemple pour faire fonctionner le plug-in est disponible dans le répertoire "GMIC-GIMP-PLUGIN-32bit-WIN" ( C:\petit-msys2-mingw-32bits-64bits-gimp28\GMIC-GIMP-PLUGIN-32bit-WIN ).
####	- L'ensemple pour faire fonctionner GMIC disponible dans le répertoire "GMIC-32bit-WIN" ( C:\petit-msys2-mingw-32bits-64bits-gimp28\GMIC-32bit-WIN ).
####
####
#### _______________________________________________________________________________________________________________________________________________________________________________________________
####
#### English translation
####
#### Script "compile_gmic_and_gmic-gimp_plugin_32_win_OPENCV.sh" to compile GMIC and the plugin G'MIC for Gimp.
#### This script is very simple:
####
####	- It compiles the plugin.
####	- It creates the entire environment for the plug-in in the "GMIC-GIMP-PLUGIN-32bit-WIN" directory (overwriting the existing directory)
####	- It creates the archive gmic_gmic-gimp_win32.tar.xz 
####
#### This script "compile_gmic_and_gmic-gimp_plugin_32_win_OPENCV.sh" works with 32-bit build environment for Windows using MSYS2 available :  http://www.aljacom.com/~gimp
#### It must be installed in "C:\petit-msys2-mingw-32bits-64bits-gimp28".
####
####
#### Use:
####    - Check the value of the variable "Repertoire_Source" in this file.
####    - Edit this file, set correct values of the variables : Stable="yes"  or   Stable="no"  and  version_gmic=\"samj_20150414\"
####	- Start MSYS clicking "start_MSYS2_GCC492-32bit.bat".
####	- Enter the two command lines that follow.
####			cd /env
####			./compile_gmic_and_gmic-gimp_plugin_32_win.sh
####	- There are 87 operations to be performed. Wait for the message "FIN - END".
####	- The plug-in is available in the "GMIC-GIMP-PLUGIN-32bit-WIN" directory ( C:\petit-msys-mingw-gimp28\GMIC-GIMP-PLUGIN-32bit-WIN ).
####	- GMIC is available in the "GMIC-32bit-WIN" directory ( C:\petit-msys2-mingw-32bits-64bits-gimp28\GMIC-32bit-WIN ).
####
####
#### version 18  20150624  par samj le 24 juin 2015      Version faite pour le nouvel environnement MSYS2 
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

version_gmic=\"samj_20150623\"


if [[ $Stable == "yes" ]]
	then 
		#### en attente d'un flag pour version stable
		commande_version=-std
		version_gmic=c++11
else		
		commande_version=-Dgmic_prerelease
fi


echo $commande_version=$version_gmic



Nombre_Operations=87
Repertoire_Source=/env/gmic/src
Repertoire_Plugin=/env/GMIC-GIMP-PLUGIN-32bit-WIN
Repertoire_GMIC=/env/GMIC-32bit-WIN


echo 01/$Nombre_Operations
cd $Repertoire_Source

echo 02/$Nombre_Operations
/mingw32/bin/i686-w64-mingw32-g++.exe -o gmic_gimp.o -c gmic.cpp -fopenmp -Dcimg_use_curl -Dcimg_use_openmp -Dgmic_build -DPSAPI_VERSION=1 -Dgmic_gimp $commande_version=$version_gmic -std=c++11 -I/mingw32/i686-w64-mingw32/include -I/mingw/include -I/python/include -pipe -O3 -mms-bitfields -march=i686 -s -Wall -W -mtune=generic -Dcimg_use_vt100 -Dgmic_is_parallel -Dgmic_is_beta=1 -Dcimg_use_fftw3 -Dcimg_use_png -Dcimg_use_zlib -Dcimg_use_tiff -Dcimg_use_jpeg -Dcimg_display=2 -Dcimg_use_rng -Dgmic_gimp -Dgmic_check_image

echo 03/$Nombre_Operations
/mingw32/bin/i686-w64-mingw32-g++.exe -o gmic_gimp.exe gmic_gimp.cpp gmic_gimp.o -fopenmp -Dcimg_use_curl -Dcimg_use_openmp `gimptool-2.0.exe --cflags` -Dgmic_build  -DPSAPI_VERSION=1 -Dgmic_gimp $commande_version=$version_gmic -std=c++11 -I/mingw32/i686-w64-mingw32/include -I/mingw/include -I/python/include -pipe -O3 -mms-bitfields -march=i686 -s -Wall -W -mtune=generic -Dcimg_use_vt100 -Dgmic_is_parallel -Dgmic_is_beta=1 -Dcimg_use_fftw3 -Dcimg_use_png -Dcimg_use_zlib -Dcimg_use_tiff -Dcimg_use_jpeg -Dcimg_use_vt100 -Dcimg_display=2 -Dcimg_use_rng -Dgmic_check_image `gimptool-2.0.exe --libs` -L/mingw32/i686-w64-mingw32/lib -L/mingw/lib -mwindows -lpthread -lm -lfftw3 -lpng16 -lz -ltiff -ljpeg -lgomp -lcurl -lpsapi 

echo 04/$Nombre_Operations
#### temporisation...
/mingw32/bin/strip.exe -V
/mingw32/bin/strip.exe gmic_gimp.exe


echo 05/$Nombre_Operations
rm -f -r $Repertoire_Plugin

echo 06/$Nombre_Operations
mkdir $Repertoire_Plugin

echo 07/$Nombre_Operations
cp /mingw32/bin/libgcc_s_dw2-1.dll $Repertoire_Plugin

echo 08/$Nombre_Operations
cp /mingw32/bin/libgomp-1.dll $Repertoire_Plugin

echo 09/$Nombre_Operations
cp /mingw32/bin/libstdc++-6.dll $Repertoire_Plugin

echo 10/$Nombre_Operations
cp /mingw32/bin/libwinpthread-1.dll $Repertoire_Plugin

echo 11/$Nombre_Operations
cp /mingw32/bin/libcurl-4.dll $Repertoire_Plugin

echo 12/$Nombre_Operations
cp /mingw32/bin/libfftw3-3.dll $Repertoire_Plugin

#  libgdk-win32-2.0-0.dll   libgdk_pixbuf-2.0-0.dll   libgimp-2.0-0.dll   libgimpui-2.0-0.dll   libgimpwidgets-2.0-0.dll   libglib-2.0-0.dll   libgobject-2.0-0.dll   libgtk-win32-2.0-0.dll   

echo 13/$Nombre_Operations
cp /mingw32/bin/libjpeg-9.dll $Repertoire_Plugin

echo 14/$Nombre_Operations
cp /mingw32/bin/libpng16-16.dll $Repertoire_Plugin

echo 15/$Nombre_Operations
cp /mingw32/bin/libtiff-5.dll $Repertoire_Plugin

echo 16/$Nombre_Operations
cp /mingw32/bin/zlib1.dll $Repertoire_Plugin

echo 17/$Nombre_Operations
cp /mingw32/bin/libeay32.dll $Repertoire_Plugin

echo 18/$Nombre_Operations
cp /mingw32/bin/libidn-11.dll $Repertoire_Plugin

echo 19/$Nombre_Operations
cp /mingw32/bin/libjbig-0.dll $Repertoire_Plugin

echo 20/$Nombre_Operations
cp /mingw32/bin/librtmp-1.dll $Repertoire_Plugin

echo 21/$Nombre_Operations
cp /mingw32/bin/ssleay32.dll $Repertoire_Plugin

echo 22/$Nombre_Operations
cp /mingw32/bin/libgmp-10.dll $Repertoire_Plugin

echo 23/$Nombre_Operations
cp /mingw32/bin/libgnutls-30.dll $Repertoire_Plugin

echo 24/$Nombre_Operations
cp /mingw32/bin/libhogweed-4-1.dll $Repertoire_Plugin

echo 25/$Nombre_Operations
cp /mingw32/bin/libnettle-6-1.dll $Repertoire_Plugin

echo 26/$Nombre_Operations
cp /mingw32/bin/libp11-kit-0.dll $Repertoire_Plugin

echo 27/$Nombre_Operations
cp /mingw32/bin/libtasn1-6.dll $Repertoire_Plugin



echo 28/$Nombre_Operations
cp $Repertoire_Source/gmic_gimp.exe $Repertoire_Plugin


echo The plug-in GMIC-GIMP is compiled.
echo Now you have to be very patient because the compilation GMIC starts...





echo 29/$Nombre_Operations
/mingw32/bin/i686-w64-mingw32-g++.exe -o gmic_main.o -c gmic.cpp -fopenmp -Dcimg_use_curl -Dcimg_verbosity=3 -g -Dcimg_use_opencv -Dcimg_use_openmp -Dgmic_build -DPSAPI_VERSION=1 $commande_version=$version_gmic -std=c++11 -I/mingw/include -I/mingw32/i686-w64-mingw32/include -I/mingw32/include/opencv -I/mingw32/include/opencv2 -pipe -O3 -mms-bitfields -s -march=i686 -Wall -W -Dgmic_is_parallel -Dcimg_display=2 -Dcimg_appname=\"gmic\" -Dcimg_use_zlib -Dcimg_use_png -Dcimg_use_jpeg -Dcimg_use_fftw3 -Dcimg_use_tiff -Dgmic_split_compilation -Dgmic_main -Dgmic_check_image


echo 30/$Nombre_Operations
/mingw32/bin/i686-w64-mingw32-g++.exe -o gmic.exe gmic_main.o -fopenmp -Dcimg_use_curl -Dcimg_verbosity=3 -g -Dcimg_use_opencv -Dcimg_use_openmp -Dgmic_build -DPSAPI_VERSION=1 $commande_version=$version_gmic -std=c++11 -I/mingw/include -I/mingw32/i686-w64-mingw32/include -I/mingw32/include/opencv -I/mingw32/include/opencv2 -lm -L/mingw32/i686-w64-mingw32/lib -L/mingw/lib -s -march=i686 -lpthread -lm -lgdi32 -lfftw3 -lpng16 -lz -ltiff -ljpeg -lgomp -lcurl -lpsapi -lopencv_imgproc -lopencv_core -lopencv_highgui /mingw64/lib/libopencv_calib3d.dll.a /mingw64/lib/libopencv_contrib.dll.a /mingw64/lib/libopencv_core.dll.a /mingw64/lib/libopencv_features2d.dll.a /mingw64/lib/libopencv_flann.dll.a /mingw64/lib/libopencv_gpu.dll.a /mingw64/lib/libopencv_highgui.dll.a /mingw64/lib/libopencv_imgproc.dll.a /mingw64/lib/libopencv_legacy.dll.a /mingw64/lib/libopencv_ml.dll.a /mingw64/lib/libopencv_nonfree.dll.a /mingw64/lib/libopencv_objdetect.dll.a /mingw64/lib/libopencv_ocl.dll.a /mingw64/lib/libopencv_photo.dll.a /mingw64/lib/libopencv_stitching.dll.a /mingw64/lib/libopencv_superres.dll.a /mingw64/lib/libopencv_video.dll.a /mingw64/lib/libopencv_videostab.dll.a


echo 31/$Nombre_Operations
/mingw32/bin/strip.exe gmic.exe

echo 32/$Nombre_Operations
/mingw32/bin/i686-w64-mingw32-g++.exe -o gmic-silent.exe gmic_main.o -Dcimg_use_curl -Dcimg_verbosity=3 -g -fopenmp -Dcimg_use_opencv -Dcimg_use_openmp -Dgmic_build -DPSAPI_VERSION=1 $commande_version=$version_gmic -std=c++11 -I/mingw/include -I/mingw32/i686-w64-mingw32/include -I/mingw32/include/opencv -I/mingw32/include/opencv2 -lm -L/mingw32/i686-w64-mingw32/lib -L/mingw/lib -s -march=i686 -mwindows -lpthread -lm -lgdi32 -lfftw3 -lpng16 -lz -ltiff -ljpeg -lgomp -lcurl -lpsapi -lopencv_imgproc -lopencv_core -lopencv_highgui /mingw64/lib/libopencv_calib3d.dll.a /mingw64/lib/libopencv_contrib.dll.a /mingw64/lib/libopencv_core.dll.a /mingw64/lib/libopencv_features2d.dll.a /mingw64/lib/libopencv_flann.dll.a /mingw64/lib/libopencv_gpu.dll.a /mingw64/lib/libopencv_highgui.dll.a /mingw64/lib/libopencv_imgproc.dll.a /mingw64/lib/libopencv_legacy.dll.a /mingw64/lib/libopencv_ml.dll.a /mingw64/lib/libopencv_nonfree.dll.a /mingw64/lib/libopencv_objdetect.dll.a /mingw64/lib/libopencv_ocl.dll.a /mingw64/lib/libopencv_photo.dll.a /mingw64/lib/libopencv_stitching.dll.a /mingw64/lib/libopencv_superres.dll.a /mingw64/lib/libopencv_video.dll.a /mingw64/lib/libopencv_videostab.dll.a


echo 33/$Nombre_Operations
/mingw32/bin/strip.exe gmic-silent.exe


####																																																																																																																																																																																																																																																				


####GMICOL

echo 34/$Nombre_Operations
/mingw32/bin/i686-w64-mingw32-g++.exe -o gmicol.o -c gmic.cpp -fopenmp -Dcimg_use_curl -Dcimg_verbosity=3 -g -Dcimg_use_opencv -Dcimg_use_openmp -Dgmic_build -DPSAPI_VERSION=1 $commande_version=$version_gmic -std=c++11 -I/mingw/include -I/mingw32/i686-w64-mingw32/include -I/mingw32/include/opencv -I/mingw32/include/opencv2 -pipe -O3 -mms-bitfields -s -march=i686 -Wall -W -Dgmic_is_parallel -Dcimg_display=0 -Dcimg_appname=\"gmic\" -Dcimg_use_zlib -Dcimg_use_png -Dcimg_use_jpeg -Dcimg_use_fftw3 -Dcimg_use_tiff -Dgmic_split_compilation -Dgmic_main -Dgmic_check_image


echo 35/$Nombre_Operations
/mingw32/bin/i686-w64-mingw32-g++.exe -o gmicol.exe gmicol.o -fopenmp -Dcimg_use_curl -Dcimg_verbosity=3 -g -Dcimg_use_opencv -Dcimg_use_openmp -Dgmic_build -DPSAPI_VERSION=1 $commande_version=$version_gmic -std=c++11 -I/mingw/include -I/mingw32/i686-w64-mingw32/include -I/mingw32/include/opencv -I/mingw32/include/opencv2 -lm -L/mingw32/i686-w64-mingw32/lib -L/mingw/lib -s -march=i686 -lpthread -lm -lgdi32 -lfftw3 -lpng16 -lz -ltiff -ljpeg -lgomp -lcurl -lpsapi -lopencv_imgproc -lopencv_core -lopencv_highgui /mingw64/lib/libopencv_calib3d.dll.a /mingw64/lib/libopencv_contrib.dll.a /mingw64/lib/libopencv_core.dll.a /mingw64/lib/libopencv_features2d.dll.a /mingw64/lib/libopencv_flann.dll.a /mingw64/lib/libopencv_gpu.dll.a /mingw64/lib/libopencv_highgui.dll.a /mingw64/lib/libopencv_imgproc.dll.a /mingw64/lib/libopencv_legacy.dll.a /mingw64/lib/libopencv_ml.dll.a /mingw64/lib/libopencv_nonfree.dll.a /mingw64/lib/libopencv_objdetect.dll.a /mingw64/lib/libopencv_ocl.dll.a /mingw64/lib/libopencv_photo.dll.a /mingw64/lib/libopencv_stitching.dll.a /mingw64/lib/libopencv_superres.dll.a /mingw64/lib/libopencv_video.dll.a /mingw64/lib/libopencv_videostab.dll.a


echo 36/$Nombre_Operations
/mingw32/bin/strip.exe gmicol.exe

echo 37/$Nombre_Operations
/mingw32/bin/i686-w64-mingw32-g++.exe -o gmicol-silent.exe gmicol.o -Dcimg_use_curl -Dcimg_verbosity=3 -g -fopenmp -Dcimg_use_opencv -Dcimg_use_openmp -Dgmic_build -DPSAPI_VERSION=1 $commande_version=$version_gmic -std=c++11 -I/mingw/include -I/mingw32/i686-w64-mingw32/include -I/mingw32/include/opencv -I/mingw32/include/opencv2 -lm -L/mingw32/i686-w64-mingw32/lib -L/mingw/lib -s -march=i686 -mwindows -lpthread -lm -lgdi32 -lfftw3 -lpng16 -lz -ltiff -ljpeg -lgomp -lcurl -lpsapi -lopencv_imgproc -lopencv_core -lopencv_highgui /mingw64/lib/libopencv_calib3d.dll.a /mingw64/lib/libopencv_contrib.dll.a /mingw64/lib/libopencv_core.dll.a /mingw64/lib/libopencv_features2d.dll.a /mingw64/lib/libopencv_flann.dll.a /mingw64/lib/libopencv_gpu.dll.a /mingw64/lib/libopencv_highgui.dll.a /mingw64/lib/libopencv_imgproc.dll.a /mingw64/lib/libopencv_legacy.dll.a /mingw64/lib/libopencv_ml.dll.a /mingw64/lib/libopencv_nonfree.dll.a /mingw64/lib/libopencv_objdetect.dll.a /mingw64/lib/libopencv_ocl.dll.a /mingw64/lib/libopencv_photo.dll.a /mingw64/lib/libopencv_stitching.dll.a /mingw64/lib/libopencv_superres.dll.a /mingw64/lib/libopencv_video.dll.a /mingw64/lib/libopencv_videostab.dll.a


echo 38/$Nombre_Operations
/mingw32/bin/strip.exe gmicol-silent.exe





echo 39/$Nombre_Operations
rm -f -r $Repertoire_GMIC

echo 40/$Nombre_Operations
mkdir $Repertoire_GMIC




echo 41/$Nombre_Operations
cp /mingw32/bin/libgcc_s_dw2-1.dll $Repertoire_GMIC

echo 42/$Nombre_Operations
cp /mingw32/bin/libgomp-1.dll $Repertoire_GMIC

echo 43/$Nombre_Operations
cp /mingw32/bin/libstdc++-6.dll $Repertoire_GMIC

echo 44/$Nombre_Operations
cp /mingw32/bin/libwinpthread-1.dll $Repertoire_GMIC

echo 45/$Nombre_Operations
cp /mingw32/bin/libcurl-4.dll $Repertoire_GMIC

echo 46/$Nombre_Operations
cp /mingw32/bin/libfftw3-3.dll $Repertoire_GMIC

echo 47/$Nombre_Operations
cp /mingw32/bin/libjpeg-9.dll $Repertoire_GMIC

echo 48/$Nombre_Operations
cp /mingw32/bin/libpng16-16.dll $Repertoire_GMIC

echo 49/$Nombre_Operations
cp /mingw32/bin/libtiff-5.dll $Repertoire_GMIC

echo 50/$Nombre_Operations
cp /mingw32/bin/zlib1.dll $Repertoire_GMIC

echo 51/$Nombre_Operations
cp /mingw32/bin/libeay32.dll $Repertoire_GMIC

echo 52/$Nombre_Operations
cp /mingw32/bin/libidn-11.dll $Repertoire_GMIC

echo 53/$Nombre_Operations
cp /mingw32/bin/libjbig-0.dll $Repertoire_GMIC

echo 54/$Nombre_Operations
cp /mingw32/bin/librtmp-1.dll $Repertoire_GMIC

echo 55/$Nombre_Operations
cp /mingw32/bin/ssleay32.dll $Repertoire_GMIC

echo 56/$Nombre_Operations
cp /mingw32/bin/libgmp-10.dll $Repertoire_GMIC

echo 57/$Nombre_Operations
cp /mingw32/bin/libgnutls-30.dll $Repertoire_GMIC

echo 58/$Nombre_Operations
cp /mingw32/bin/libhogweed-4-1.dll $Repertoire_GMIC

echo 59/$Nombre_Operations
cp /mingw32/bin/libnettle-6-1.dll $Repertoire_GMIC

echo 60/$Nombre_Operations
cp /mingw32/bin/libp11-kit-0.dll $Repertoire_GMIC

echo 61/$Nombre_Operations
cp /mingw32/bin/libtasn1-6.dll $Repertoire_GMIC

echo 62/$Nombre_Operations
cp /mingw32/bin/libssh2-1.dll $Repertoire_GMIC

echo 63/$Nombre_Operations
cp /mingw32/bin/tbb.dll $Repertoire_GMIC

echo 64/$Nombre_Operations
cp /mingw32/bin/libHalf-2_2.dll $Repertoire_GMIC

echo 65/$Nombre_Operations
cp /mingw32/bin/libIlmImf-2_2.dll $Repertoire_GMIC

echo 66/$Nombre_Operations
cp /mingw32/bin/libjasper-1.dll $Repertoire_GMIC

echo 67/$Nombre_Operations
cp /mingw32/bin/libjpeg-8.dll $Repertoire_GMIC

echo 68/$Nombre_Operations
cp /mingw32/bin/liblzma-5.dll $Repertoire_GMIC

echo 69/$Nombre_Operations
cp /mingw32/bin/libiconv-2.dll $Repertoire_GMIC

echo 70/$Nombre_Operations
cp /mingw32/bin/libintl-8.dll $Repertoire_GMIC

echo 71/$Nombre_Operations
cp /mingw32/bin/libIex-2_2.dll $Repertoire_GMIC

echo 72/$Nombre_Operations
cp /mingw32/bin/libIlmThread-2_2.dll $Repertoire_GMIC

echo 73/$Nombre_Operations
cp /mingw32/bin/libImath-2_2.dll $Repertoire_GMIC

echo 74/$Nombre_Operations
cp /mingw32/bin/libffi-6.dll $Repertoire_GMIC




#### OpenCV


echo 75/$Nombre_Operations
cp /mingw32/bin/libopencv_core2411.dll $Repertoire_GMIC

echo 76/$Nombre_Operations
cp /mingw32/bin/libopencv_highgui2411.dll $Repertoire_GMIC



echo 77/$Nombre_Operations
cp $Repertoire_Source/gmic.exe $Repertoire_GMIC

echo 78/$Nombre_Operations
cp $Repertoire_Source/gmic-silent.exe $Repertoire_GMIC


####GMICOL
echo 79/$Nombre_Operations
cp $Repertoire_Source/gmicol.exe $Repertoire_GMIC

echo 80/$Nombre_Operations
cp $Repertoire_Source/gmicol-silent.exe $Repertoire_GMIC



echo 81/$Nombre_Operations
rm -f $Repertoire_Source/Start_Terminal_With_Test_GMIC.bat

echo 82/$Nombre_Operations
echo -e "cmd /T:0f /E:ON /K \"prompt $G&&cls&&gmic -verbose - 256,256,1,4 -gimp_chessboard 32,32,0,0,0,1,0,0,0,255,255,255,255,255 -window -1,-1,0,-1,TEST -wait 500&&echo Current Directory = %CD%&&echo You can type or paste a command recognized by GMIC&&echo For example :    gmic 256,256,1,4 -gimp_chessboard 32,32,0,0,0,1,0,0,0,255,255,255,255,255\"\n" > Start_Terminal_With_Test_GMIC.bat

echo 83/$Nombre_Operations
cp $Repertoire_Source/Start_Terminal_With_Test_GMIC.bat $Repertoire_GMIC

echo 84/$Nombre_Operations
rm -f $Repertoire_Source/Start_Terminal_With_Test_GMIC.bat

echo GMIC is compiled.
echo Creating the  gmic_gmic-gimp_win32.tar.xz  archive...

echo 85/$Nombre_Operations
rm -f /env/gmic_gmic-gimp_win32.tar.xz

echo 86/$Nombre_Operations
/usr/bin/tar.exe -cf /env/gmic_gmic-gimp_win32.tar /env/GMIC-32bit-WIN /env/GMIC-GIMP-PLUGIN-32bit-WIN

echo 87/$Nombre_Operations
/usr/bin/xz.exe -ze /env/gmic_gmic-gimp_win32.tar


echo FIN - END