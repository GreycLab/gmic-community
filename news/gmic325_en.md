# G’MIC 3.2.5 : 15 years of development for open and reproducible image processing

To celebrate the release of version **3.2.5** of [_G’MIC_](https://gmic.eu) (_GREYC’s Magic for Image Computing_), an open [framework](https://en.wikipedia.org/wiki/Software_framework) for [digital image processing](https://en.wikipedia.org/wiki/Digital_image_processing), we present you with a summary of the new features implemented since our [previous report](https://linuxfr.org/news/sortie-de-g-mic-3-0-une-troisieme-dose-pour-un-traitement-efficace-de-vos-images) (published during December of 2021). It is also the opportunity for us to celebrate the project's **15 years** of existence!

_G’MIC_ is being developed in [Caen](https://en.wikipedia.org/wiki/Caen), in France, by the [_IMAGE_](https://www.greyc.fr/image) team  of [_GREYC_](https://www.greyc.fr), a public research lab in Information and Communication Sciences and Technologies (Joint Research Unit [_CNRS_](https://www.cnrs.fr/) / [_ENSICAEN_](https://www.ensicaen.fr/) / [Université de Caen](https://www.unicaen.fr/)). It is distributed under the free [_CeCILL_](http://www.cecill.info/licences/Licence_CeCILL_V2.1-en.html) licence.

[![gmic_teaser](https://gmic.eu/gmic325/thumbs/greyc.png)](https://gmic.eu/gmic325/img/greyc.jpg)

In this report, we will explain in detail a few of the recently added features, and illustrate them with examples of 2D and 3D image processing and synthesis.

_A. N. : Click on images to see a full resolution version, or a link to the video for images showing the icon ![play_video](https://gmic.eu/gmic325/thumbs/icon_play_video.png)_

----

* [The G’MIC project](https://gmic.eu)
* [The Project's Mastodon news feed](https://piaille.fr/@gmic)
* [Série d’articles G’MIC sur LinuxFr.org](https://linuxfr.org/tags/gmic/public)

----

# 1. What is _G’MIC_ ?


[_G’MIC_](https://gmic.eu) is an open [digital image](https://en.wikipedia.org/wiki/Digital_image) manipulation and processing framework. It provides various user interfaces allowing algorithmic manipulation of images and signals. The heart of this project is based on the implementation of a scripting language (the [_« G’MIC language »_](https://gmic.eu/reference/overall_context.html)),
specifically designed to ease the prototyping and implementation of new image processing algorithms and operators. Users can apply operators among several hundreds already available, but they also have the capability of writing their own processing pipelines and making them available through the various user interfaces of the project. It is therefore, in essence, an open, expandable and constantly evolving framework.

_G’MIC_'s most accomplished user interfaces are : [`gmic`](https://gmic.eu/reference/), the command line interface (useful addition to [_ImageMagick_](https://www.imagemagick.org/) or [_GraphicsMagick_](http://www.graphicsmagick.org) for people who like to use the terminal), the Web service [_G’MIC Online_](https://gmicol.greyc.fr/), and above all, the plug-in [_G’MIC-Qt_](https://github.com/c-koi/gmic-qt), which can be used in numerous popular image editing software such as [_GIMP_](https://www.gimp.org), [_Krita_](https://www.krita.org), [_DigiKam_](https://www.digikam.org), [_Paint.net_](https://www.getpaint.net), [_Adobe Photoshop_](https://en.wikipedia.org/wiki/Adobe_Photoshop), [_Affinity Photo_](https://en.wikipedia.org/wiki/Affinity_Photo)…
This plug-in is very easy to use and now provides more than **580 processing filters** to augment these image manipulation software.

[![Greffon G’MIC-Qt](https://gmic.eu/gmic325/thumbs/gmic_qt_325.png)](https://gmic.eu/gmic325/img/gmic_qt_325.jpg) _Fig. 1.1. Preview of the G’MIC-Qt plug-in, in version **3.2.5**, here launched from GIMP 2.10._


Thanks to its dedicated scripting language, new filters and effects are regularly added to _G’MIC_.


In this article, we will describe a few of these new filter effects and give some news about the project. We will also show some examples for the `gmic` command line tool, which is by far the most powerful interface provided by the project.


# 2. New abstraction, _Glitch Art_ and pattern generation filters


- To begin this new features report, let's mention the existence of a new transformation filter which converts images to [Line Art](https://en.wikipedia.org/wiki/Line_art) drawings. This filter, appropriately named **Artistic / Line Art** was conceived by [Claude Lion](https://github.com/cl4cnam), an external contributor who is already the author of multiple filters (such as the very appreciated **Artistic / Comic Book**, [already mentioned EN LINK?](https://linuxfr.org/news/sortie-de-g-mic-3-0-une-troisieme-dose-pour-un-traitement-efficace-de-vos-images#toc-21-effets-artistiques) in our previous article.

This filter anlyses the geometry of the main structures in images and decides if these structures should appear in a picture redrawn on a white background, either as black lines or as gray or black filled regions. It is particularly effective on portraits, since the contrasts are rather well marked marked in this type of images.


[![filter_lineart](https://gmic.eu/gmic325/thumbs/filter_lineart.png)](https://gmic.eu/gmic325/img/filter_lineart.jpg) _Fig. 2.1. The **Artistic / Line Art** filter, as seen in the G’MIC-Qt plug-in._


The interactive preview of the _G’MIC-Qt_ plug-in alleviates the adjustment of all the filter's settings to personalize the expected results. Pressing either the « _Apply_ » or « _OK_ » button applies the filter to the picture. Note that once these settings are selected, pressing the _« Copy to Clipboard »_ button in the plug-in's interface will copy the corresponding _G’MIC_ command to the clipboard.


[![filter_lineart_zoom](https://gmic.eu/gmic325/thumbs/filter_lineart_zoom.png)](https://gmic.eu/gmic325/img/filter_lineart_zoom.jpg) _Fig. 2.2. The « Copy to Clipboard » button adds the G'MIC command corresponding to the filter's action to the clipboard._


Then, to apply the effect with the same parameters on different images (for batch processing), all you need is to launch `gmic` in a terminal, add the filename of the image to process, followed by the command previously copied to the clipboard, which will give something like this:

```sh
$ gmic autre_portrait.jpg cl_lineart 0,0,2,1,15,15,1,0,6,2,2,0,0,0,50,50 output lineart.png
```


This method is useful when one wants to use certain _G’MIC_ effects inside personalized scripts (this obviously works with all the filters available in the plug-in).


[![lineart](https://gmic.eu/gmic325/thumbs/lineart.png)](https://gmic.eu/gmic325/img/lineart.jpg) _Fig. 2.3. The « Line Art » filter, applied on another portrait image, with the same settings, from the terminal._


[![lineart](https://gmic.eu/gmic325/thumbs/lineart2.png)](https://gmic.eu/gmic325/img/lineart2.jpg) _Fig. 2.4. The « Line Art » filter, applied on a few other example images._


- Now, let's take a look at the **Degradations / Huffman Glitches** filter, a fun way to generate [_Glitch Art_](https://en.wikipedia.org/wiki/Glitch_art). More precisely, here we will simulate image decompression artifacts with the deliberate addition of errors (bits inversion) in the [Huffman codes](https://en.wikipedia.org/wiki/Huffman_coding) which would have been used for the lossless compression of the input picture's data. This produces visible digital distortions on the picture when the altered data is decompressed, distortions which actually are the effects sought by the _Glitch Art_ aficionados!

[![huffman_glitches](https://gmic.eu/gmic325/thumbs/huffman_glitches.png)](https://gmic.eu/gmic325/img/huffman_glitches.jpg) _Fig. 2.5. The **Degradations / Huffman Glitches** filter, as seen in the G’MIC-Qt plug-in._


This filter allows the generation of compression artifacts with variations : block by block, line by line, column by column, or on image data encoded in color spaces other than _RGB_. Ce filtre permet la génération d’artéfacts de compression avec des variations : bloc par bloc, ligne par ligne, colonne par colonne, ou sur des données image encodées dans des espaces couleur différents de _RGB_. In the end, the diversity of anomalies it is possible to produce is quite large, as depicted on the following figure:


[![huffman_glitches2](https://gmic.eu/gmic325/thumbs/huffman_glitches2.png)](https://gmic.eu/gmic325/img/huffman_glitches2.jpg) _Fig. 2.6. A few variations of the **Degradations / Huffman Glitches** filter settings._


Here again, it is easy to retrieve the _G’MIC_ command corresponding to the filter's operation, use it in a script, and, for example, apply this effect on all the _frames_ of a video (click on the picture below to view the video) :


[![v_huffman_glitches](https://gmic.eu/gmic325/thumbs/v_huffman_glitches.png)](https://gmic.eu/gmic325/img/v_huffman_glitches.mp4) _Fig. 2.7. The **Degradations / Huffman Glitches** filter applied on the [_Tears of Steel_](https://en.wikipedia.org/wiki/Tears_of_Steel) video by the [Blender foundation](https://en.wikipedia.org/wiki/Blender_Foundation)._

There floats like the sweet scent of an analog TV set in the air...☺

- Let's also mention the appearance of a new filter, named **Patterns / Pack Ellipses**, which may not be entirely pleasing to our [trypophobic](https://en.wikipedia.org/wiki/Trypophobia) readers (not at all related to the phobia of eating "tripes à la mode de Caen" )! The goal of this filter is to redraw an image by fitting together colored ellipses, yet preventing them to touch each other. Ellipses are oriented parallel or orthogonal to the local structures, to make the most visible edges of images stick out. This is not the first filter of this kind in _G’MIC_, but here we have a new [sphere packing]https://en.wikipedia.org/wiki/Sphere_packing) algorithm, which executes quickly and produces interesting pictures.

[![pack_ellipses](https://gmic.eu/gmic325/thumbs/pack_ellipses.png)](https://gmic.eu/gmic325/img/pack_ellipses.jpg) _Fig. 2.8. The **Patterns / Pack Ellipses** filter, as seen in the G’MIC-Qt plug-in._


[![pack_ellipses2](https://gmic.eu/gmic325/thumbs/ellipses.png)](https://gmic.eu/gmic325/img/ellipses.jpg) _Fig. 2.9. Application of the **Patterns / Pack Ellipses** filter on different portrait images._


The video below is a step by step illustration of the algorithm's behaviour while fitting colored circles to reconstruct a portrait image :


[![v_circle_packing](https://gmic.eu/gmic325/thumbs/v_circle_packing.png)](https://gmic.eu/gmic325/img/v_circle_packing.mp4) _Fig. 2.10. A video breakdown of the different steps of the **Patterns / Pack Ellipses** filter._


- Still among the textures and patterns generation effects, let's point out the appearance of a new [_Halftoning_](https://en.wikipedia.org/wiki/Halftone) filter, named **Patterns / Halftone [Generic]**. Here again, the idea is to reconstruct an input image by stacking small colored patterns of any shape, such as small circles for instance :

[![halftone_generic](https://gmic.eu/gmic325/thumbs/halftone_generic.png)](https://gmic.eu/gmic325/img/halftone_generic.jpg) _Fig. 2.11. The **Patterns / Halftone [Generic]** filter, as seen in the  G’MIC-Qt plug-in._


Or a spiral :


[![halftone_generic2](https://gmic.eu/gmic325/thumbs/halftone_generic2.png)](https://gmic.eu/gmic325/img/halftone_generic2.jpg) _Fig. 2.12. The **Patterns / Halftone [Generic]** filter with a spiral pattern._


The filter even provides a special mode so that the user can provide his own personalized _Halftoning_ pattern design on a separate layer :


[![halftone_generic3](https://gmic.eu/gmic325/thumbs/halftone_generic3.png)](https://gmic.eu/gmic325/img/halftone_generic3.jpg) _Fig. 2.13. The **Patterns / Halftone [Generic]** filter with a personalized pattern design._


From an algorithmic point of view, the idea is to locally erode or dilate the pattern passed as a filter parameter to best encode the grayscale value of each pixel of the input image.


- The following filter has an amusing story : subscribed to the _Twitter_ account of the artist [Memo Akten](https://www.memo.tv/), one day I stumbled upon [this tweet](https://twitter.com/memotv/status/1556619064491102209) describing a generative art algorithm that Memo imagined (but did not implement). It was a good opportunity to try to implement it in the _G’MIC_ language, just for the fun of experimenting!  Once it was done, creating a filter usable from the _G’MIC-Qt_ plug-in was self-evident. The result is the **Rendering / Algorithm A** filter, which creates « [Mondrian-like](https://en.wikipedia.org/wiki/Piet_Mondrian) » abstract illustrations.

[![algorithmA](https://gmic.eu/gmic325/thumbs/algorithmA.png)](https://gmic.eu/gmic325/img/algorithmA.jpg) _Fig. 2.14. The filter **Patterns / Algorithm A**, as seen in the G’MIC-Qt plug-in._

Image generation is largely based on drawing random numbers.
La génération des images repose largement sur le tirage de nombres aléatoires. From a simple command line, one can easily produce many different artworks in one go :

```sh
$ gmic repeat 6 { 500,500,1,3 fx_memoakten_algorithm_a[-1] '$>',20,30,30,2,50,10,50,40,3,60,1,0,0,0,255,255,255,255,0,0,255,128,0,255,255,0,0,0,0 } frame 1,1,0 frame 5,5,255 append_tiles 3 output output.png
```

which synthesizes the following image :


[![algorithmA2](https://gmic.eu/gmic325/thumbs/algorithmA2.png)](https://gmic.eu/gmic325/img/algorithmA2.jpg) _Fig. 2.15. An « artworks » Patchwork produced by the **Patterns / Algorithm A** filter._


- Still in order to produce bizarre and abstract pictures, let's talk about the **Arrays & Tiles / Shuffle Patches** filter, which will break down an input image into a thumbnail array (« _patches_ »), then shuffle these _patches_ spatially before joining them to produce the resulting image. Different options are offered, allowing a random rotation of the _patches_, or reassembling overlapping _patches_.

[![shuffle_patches](https://gmic.eu/gmic325/thumbs/shuffle_patches.png)](https://gmic.eu/gmic325/img/shuffle_patches.jpg) _Fig. 2.16. The **Arrays & Tiles / Shuffle Patches** filter, as seen in the G’MIC-Qt plug-in._

The result is an image resembling a patchwork of different parts of the original picture, with overall similar colors, but where the natural order of structures is lost.


[![shuffle_patches2](https://gmic.eu/gmic325/thumbs/shuffle_patches2.png)](https://gmic.eu/gmic325/img/shuffle_patches2.jpg) _Fig. 2.17. Result of the **Arrays & Tiles / Shuffle Patches** filter applied to a landscape picture._


And again, we can apply this filter to all the _frames_ of a video, as illustrated in the example below (of course you will have recognized the short movie [_Big Buck Bunny_](https://en.wikipedia.org/wiki/Big_Buck_Bunny) by the [Blender_foundation](https://en.wikipedia.org/wiki/Blender_Foundation)).


[![shuffle_patches2](https://gmic.eu/gmic325/thumbs/v_shuffle_patches.png)](https://gmic.eu/gmic325/img/v_shuffle_patches.mp4) _Fig. 2.18. The **Arrays & Tiles / Shuffle Patches** filter applied to the [_Big Buck Bunny_](https://en.wikipedia.org/wiki/Big_Buck_Bunny) video by the [Blender_foundation](https://en.wikipedia.org/wiki/Blender_Foundation))._


- And to close this section about image abstraction, _Glitch Art_ and pattern generation, here is the **Patterns / Pills** filter, which creates a periodic (repeating) texture resembling a stack of « pills » rotated 90° to each other.

[![pills](https://gmic.eu/gmic325/thumbs/pills.png)](https://gmic.eu/gmic325/img/pills.jpg) _Fig. 2.19. The **Patterns / Pills**, as seen in the G’MIC-Qt plug-in._

Nothing too complicated : this filter is a straight implementation of the folowwing mathematical formula :

[![pills_formula](https://gmic.eu/gmic325/thumbs/pills_formula.png)](https://gmic.eu/gmic325/img/pills_formula.jpg)

This nice formula was imagined by [Miloslav Číž](https://en.wikipedia.org/wiki/User:Drummyfish), and described on [this page](https://commons.wikimedia.org/wiki/File:2D_function_pills.png). It was tempting to create a new filter available to everyone!

Note that we can produce the same base image, directly from the original formula, once again by executing the `gmic` command line :

```sh
$ gmic 600,600,1,1,"X = x*30/w; Y = y*30/h; sqrt(abs(sin(X + cos(Y + sin(X + cos(Y)))) * sin(Y + cos(X + sin(Y + cos(X))))))" normalize 0,255
```

Nevertheless, the **Patterns / Pills** found in the _G’MIC-Qt_ plug-in allows some additional variations, like the possibility of specifying a rotation angle or independently creating these patterns for each _RGB_ channel of the output image.


# 3. Nouveautés concernant le traitement des couleurs


## 3.1. Fonctionnalités pour les _LUTs_ 3D


_G’MIC_ est un logiciel de traitement d’images qui intègre nativement beaucoup de [_LUTs 3D_ couleur]((https://en.wikipedia.org/wiki/3D_lookup_table)) différentes (1045 à ce jour), en particulier grâce à un algorithme performant de compression de _LUTs_ issu de nos travaux de recherche (décrit dans [une dépêche précédente](https://linuxfr.org/news/g-mic-2-7-0-une-rentree-pleine-de-style-pour-le-traitement-d-images#toc-4-toujours-plus-de-transformations-colorim%C3%A9triques)). Ces _LUTs_ 3D couleur définissent des fonctions de transformation des couleurs d’une image, souvent pour lui donner une ambiance particulière. Récemment, de nouvelles commandes pour faciliter la visualisation et la création de _LUTs_ 3D couleur ont été ajoutées à _G’MIC_ :


- La commande [`display_clut`](https://gmic.eu/reference/display_clut) fait le rendu 3D d’une _LUT_ couleur, ce qui permet de visualiser la transformation _RGB → RGB_ qu’elle représente. Par exemple, la commande :


```sh
$ gmic clut summer clut spy29 display_clut 400 text_outline[0] Summer text_outline[1] "Spy 29"
```





affichera :


[![display_clut](https://gmic.eu/gmic325/thumbs/display_clut.png)](https://gmic.eu/gmic325/img/display_clut.jpg) _Fig. 3.1.1. La commande `display_clut` affiche une vue 3D d’une _LUT_ couleur._


- La commande [`random_clut`](https://gmic.eu/reference/random_clut), quant à elle, produit une _LUT_ 3D couleur aléatoire, possédant certaines propriétés de continuité des couleurs. Par exemple, la commande suivante :


```sh
$ gmic sample colorful resize2dx 320 repeat 4 { random_clut +map_clut[0] [-1] display_clut[-2] 320 to_rgb[-2] append[-2,-1] y } frame 2,2,0 to_rgba append x,1
```





synthétisera une image du style de celle ci-dessous :


[![random_clut](https://gmic.eu/gmic325/thumbs/random_clut.png)](https://gmic.eu/gmic325/img/random_clut.jpg) _Fig. 3.1.2. Différentes _LUTs_ 3D couleur aléatoires, obtenues via la commande `random_clut`, et appliquées sur une image couleur._


## 3.2. Nouveaux filtres couleurs pour le greffon _G'MIC-QT_.


- Assez logiquement, la commande `random_clut` est à la base de l’implémentation du nouveau filtre **Colors / Random Color Transformation**, apparu dans le greffon _G’MIC-Qt_, qui applique une transformation colorimétrique aléatoire sur une image d’entrée.


[![random_color_transformation](https://gmic.eu/gmic325/thumbs/random_color_transformation.png)](https://gmic.eu/gmic325/img/random_color_transformation.jpg) _Fig. 3.2.1. Le filtre **Colors / Random Color Transformation**, tel qu’il apparaît dans le greffon G’MIC-Qt._


- Pour rester dans le domaine des _LUTs_ 3D couleur, mentionnons l’apparition du filtre **Colors / Apply From CLUT Set**, qui permet de transformer une image couleur en lui appliquant l’une des _LUTs_ 3D définies dans un _pack_ de _LUTs_, stocké lui-même sous la forme d’un fichier d’extension `.gmz`.


Quelques explications sont nécessaires : le format de fichier `.gmz` est implémenté et utilisé par _G’MIC_ pour la sérialisation et la sauvegarde de données binaires génériques compressées.
Ainsi, comment produire un fichier `.gmz` stockant un ensemble de _LUTs_ 3D couleur compressées, pour alimenter le filtre **Colors / Random Color Transformation** ? Prenons l’exemple concret du _pack_ de 10 _LUTs_ proposé gracieusement [sur cette page web](https://www.editingcorp.com/free-hand-picked-luts-for-cinematic-color-grading/). Ces _LUTs_ sont distribuées en format `.cube`, le format le plus répandu pour le stockage des _LUTs_ 3D couleur. Ces 10 fichiers occupent **8.7 Mo** sur le disque.


[![clut_set2](https://gmic.eu/gmic325/thumbs/clut_set2.png)](https://gmic.eu/gmic325/img/clut_set2.jpg) _Fig. 3.2.2. Visualisation des 10 LUTs 3D couleur de notre cas d’exemple._


La commande suivante les compresse (avec des pertes visuellement imperceptibles) grâce à l’algorithme de compression de _LUTs_ de _G’MIC_, en un fichier [`clut_pack.gmz`](https://gmic.eu/gmic325/img/clut_pack.gmz) de **156 Ko**. Attention, ce processus de compression est long (plusieurs dizaines de minutes) !


```sh
$ gmic *.cube compress_clut , output clut_pack.gmz
```






Une fois ce fichier de _pack_ de _LUTs_ généré, ces 10 transformations couleur sont disponibles, via le filtre **Colors / Apply From CLUT Set**, en lui spécifiant le fichier `clut_pack.gmz` en paramètre, comme illustré ci-dessous.


[![clut_set](https://gmic.eu/gmic325/thumbs/clut_set.png)](https://gmic.eu/gmic325/img/clut_set.jpg) _Fig. 3.2.3. Le filtre **Colors / Apply From CLUT Set**, tel qu’il apparaît dans le greffon G’MIC-Qt._


Voilà donc un filtre évitant de stocker des _packs_ de _LUTs_ 3D couleur de plusieurs méga-octets sur son disque !


- Toujours dans le thème des transformations colorimétriques, voici le filtre récent **Colors / Vibrance**, qui rend les couleurs de vos images toujours plus chatoyantes. Ce n’est pas le premier filtre de ce type disponible dans _G’MIC_, mais on dispose ainsi d’une alternative aux algorithmes similaires déjà présents. Ce filtre émane de l’utilisateur [_Age_](https://discuss.pixls.us/u/age/), qui participe occasionnellement aux discussions sur notre [forum](https://discuss.pixls.us/c/software/gmic/), hébergé par nos amis de [PIXLS.US](https://discuss.pixls.us/) (dont [Pat David](https://patdavid.net/), également contributeur au projet [GIMP](https://www.gimp.org), est l’instigateur).


[![vibrance](https://gmic.eu/gmic325/thumbs/vibrance.png)](https://gmic.eu/gmic325/img/vibrance.jpg) _Fig. 3.2.4. Le filtre **Colors / Vibrance**, tel qu’il apparaît dans le greffon G’MIC-Qt._


## 3.3. Commandes `color2name` et `name2color`


Dernière nouveauté concernant les couleurs : les deux commandes [`color2name`](https://gmic.eu/reference/color2name) et [`name2color`](https://gmic.eu/reference/name2color), qui convertissent un code couleur _RGB_ en un nom de couleur (en anglais), et inversement. Un exemple d’utilisation est :


```sh
$ gmic 27,1,1,3 rand 0,255 split x foreach { color2name {^} resize 300,100 text_outline '${}',0.5~,0.5~,28 } frame 1,1,0 append_tiles 3
```





Cette commande construit un tableau de couleurs aléatoires nommées, sous la forme d’une image telle que :


[![color2name](https://gmic.eu/gmic325/thumbs/color2name.png)](https://gmic.eu/gmic325/img/color2name.jpg) _Fig. 3.3.1. Exemple d’utilisation de la commande `color2name` pour nommer des couleurs aléatoires._


Les associations entre les 881 noms de couleurs reconnues par ces commandes et leurs codes _RGB_ respectifs ont été récupérées [de cette page Wikipédia](https://en.wikipedia.org/wiki/Lists_of_colors). Ci-dessous, l’ensemble de ces 881 couleurs visualisées dans le cube _RGB_ :


[![color2name3d](https://gmic.eu/gmic325/thumbs/color2name3d.png)](https://gmic.eu/gmic325/img/color2name3d.jpg) _Fig. 3.3.2. Ensemble des couleurs nommées connues par la commande `color2name`._


# 4. Maillages 3D et ensembles de voxels


Saviez vous que _G’MIC_ était aussi capable de manipuler des [objets 3D maillés](https://fr.wikipedia.org/wiki/Mesh_(objet)) (« _3D Mesh_ » en anglais), en plus de gérer des images conventionnelles ? Et même si la modélisation et la visualisation 3D ne sont pas centrales dans les objectifs du projet, plusieurs ajouts intéressants ont été implémentés dans ce domaine.


## 4.1. Import d'objet en format _Wavefront_
Tout d’abord, _G’MIC_ peut désormais importer des objets 3D en format `.obj` [_Wavefront_](https://fr.wikipedia.org/wiki/Objet_3D_(format_de_fichier)), alors que seul l’export dans ce format était possible auparavant (export qui a d’ailleurs été amélioré). Toutes les caractéristiques du format `.obj` ne sont cependant pas prises en compte, mais l’import de la géométrie de l’objet, de ses couleurs et de ses textures fonctionnent en général. Ainsi, la commande :


```sh
$ gmic luigi3d.obj display3d
```





permet d’importer un objet 3D et de le visualiser dans une nouvelle fenêtre, comme l’illustre l’animation ci-dessous. Attention, le visualiseur intégré à _G’MIC_ n’utilise pas les possibilités des _GPUs_ pour l’accélération graphique. Le rendu peut donc être assez lent si le maillage comporte beaucoup de primitives (une piste d’amélioration pour le futur ?).


[![luigi3d](https://gmic.eu/gmic325/img/v_luigi3d.gif)](https://gmic.eu/gmic325/img/v_luigi3d.gif) _Fig. 4.1.1. Import et visualisation d’un maillage 3D texturé dans G’MIC._


Naturellement, nous avons intégré cette nouvelle fonctionnalité d’import de maillages 3D dans le greffon _G’MIC-Qt_, avec le nouveau filtre **Rendering / 3D Mesh**, qui permet d’importer un fichier `.obj` et d’en insérer un rendu 3D dans une image, comme l’illustre la vidéo ci-dessous :


[![mesh3d](https://gmic.eu/gmic325/thumbs/v_mesh3d.png)](https://gmic.eu/gmic325/img/v_mesh3d.mp4) _Fig. 4.1.2 Le filtre **Rendering / 3D Mesh** en action, dans le greffon G’MIC-Qt._


On l’utilisera typiquement pour importer un objet 3D du type que l’on souhaite dessiner, pour l’orienter dans l’espace, et s’en servir comme « guide » de dessin, soit en le redessinant complètement sur un calque supérieur, soit en utilisant un des nombreux filtres de _G’MIC_, par exemple pour en faire un rendu _cartoon_ ou peinture.


## 4.2. Outils de transformation des maillages 3D.


Que faire d’autre, une fois un maillage 3D chargé en mémoire ? _G’MIC_ s’est doté des fonctionnalités suivantes :


- L’extraction des textures de l’objet 3D, grâce à la nouvelle commande [`extract_textures3d`](https://gmic.eu/reference/extract_textures3d). Les trois figures suivantes illustrent un cas d’utilisation, avec l’exemple d’un objet 3D maillé de chat dont la texture est extraite, transformée avec un filtre de stylisation (basé sur le modèle de l’estampe japonaise [La Grande Vague de Kanagawa](https://fr.wikipedia.org/wiki/La_Grande_Vague_de_Kanagawa)), puis réappliquée sur le chat.


[![cat_obj](https://gmic.eu/gmic325/thumbs/cat_obj.png)](https://gmic.eu/gmic325/img/cat_obj.jpg) _Fig. 4.2.1. Vue d’un objet 3D maillé representant un chat, avec sa texture._


[![cat_textures](https://gmic.eu/gmic325/thumbs/cat_textures.png)](https://gmic.eu/gmic325/img/cat_textures.jpg) _Fig. 4.2.2. Extraction et stylisation des textures, via la commande `extract_textures3d`._


[![v_extract_texture3d](https://gmic.eu/gmic325/thumbs/v_extract_texture3d.png)](https://gmic.eu/gmic325/img/v_extract_texture3d.mp4) _Fig. 4.2.3. Visualisation du maillage 3D original et de sa version stylisée._


- On peut également subdiviser les faces d’un objet 3D, grâce à la nouvelle commande [`subdivide3d`](https://gmic.eu/reference/subdivide3d).


[![subdivide3d](https://gmic.eu/gmic325/thumbs/subdivide3d.png)](https://gmic.eu/gmic325/img/subdivide3d.jpg)  _Fig. 4.2.4. Subdivision des faces d’un maillage 3D de tore, par la commande `subdivide3d`._


- On peut convertir un objet 3D **texturé** en objet uniquement **coloré**, avec la commande [`primitives3d`](https://gmic.eu/reference/primitives3d). La commande suivante applique ce processus sur l’objet _Luigi3d_ introduit précédemment, pour lui retirer sa texture et la remplacer par des faces colorées :


```sh
$ gmic luigi3d.obj primitives3d 2 output luigi3d_no_textures.obj
```





[![primitives3d](https://gmic.eu/gmic325/thumbs/primitives3d.png)](https://gmic.eu/gmic325/img/primitives3d.jpg) _Fig. 4.2.5. Conversion des primitives texturées en primitives colorées uniquement, avec la commande `primitives3d`._


La couleur de chaque face est calculée comme la moyenne des couleurs à chacun des sommets composant la face. Pour les grandes faces, cela peut donc être très utile de subdiviser l’objet préalablement pour obtenir une résolution de texture colorée suffisante dans l’objet final (avec la commande `subdivide3d`).


- Enfin, on peut également convertir l’objet maillé 3D sous forme d’une image **volumique** contenant un ensemble de **voxels**, grâce à la nouvelle commande [`voxelize3d`](https://gmic.eu/reference/voxelize3d). Cette commande convertit toutes les primitives de base composant un objet 3D (points, faces, segments, sphères), sous la forme de primitives discrètes tracées dans l’image volumique. Par exemple, la commande :


```sh
$ gmic skull.obj voxelize3d 256,1,1 output skull_voxelized.tif display_voxels3d
```





va transformer le maillage du crane illustré ci-dessous, sous la forme d’une image volumique de voxels en couleurs, que l’on va pouvoir visualiser avec la nouvelle commande [`display_voxels3d`](https://gmic.eu/reference/display_voxels3d). D’où un rendu très « [Minecraftien](https://fr.wikipedia.org/wiki/Minecraft) » (representé ci-dessous pour différentes résolutions de voxélisation) :


[![voxelize3d](https://gmic.eu/gmic325/thumbs/voxelize3d.png)](https://gmic.eu/gmic325/img/voxelize3d.jpg) _Fig. 4.2.6. Conversion d’un maillage 3D texturé sous forme d’images volumiques composé de voxels colorés, avec la commande `voxelize3d`._


Cette fonctionnalité servira, par exemple, aux personnes étudiant le domaine de la géométrie discrète, qui pourront facilement générer des objets discrets 3D complexes à partir de maillages (souvent plus faciles à produire que leurs équivalents discrets !). La vidéo ci-dessous illustre le rendu d’un objet 3D discret obtenu de cette façon :

[![v_display_voxels3d](https://gmic.eu/gmic325/thumbs/v_nounours.png)](https://gmic.eu/gmic325/img/v_nounours.mp4) _Fig. 4.2.7. Vidéo de visualisation d’un maillage 3D complexe voxélisé par la commande `voxelize3d`._


## 4.3. Outils de génération de maillages 3D


Pour conclure cette partie dédiée aux maillages 3D dans _G’MIC_, mentionnons l’apparition de quelques commandes récentes, en vrac, pour la génération procédurale d’objets 3D maillés :


- Les commandes [`shape_menger`](https://gmic.eu/reference/shape_menger) et [`shape_mosely`](https://gmic.eu/reference/shape_mosely) produisent des représentation volumiques (images de voxels) des objets mathématiques fractals suivants : L’[éponge de Menger](https://fr.wikipedia.org/wiki/%C3%89ponge_de_Menger) et le [flocon de Mosely](https://fr.wikipedia.org/wiki/Flocon_de_Mosely).


[![menger_sponge](https://gmic.eu/gmic325/thumbs/menger_sponge.png)](https://gmic.eu/gmic325/img/menger_sponge.jpg) _Fig. 4.3.1. Rendus 3D de l’éponge de Menger et du flocon de Mosely, crées avec les commandes `shape_menger` et `shape_mosely`._


[![v_menger_sponge](https://gmic.eu/gmic325/thumbs/v_menger_sponge.png)](https://gmic.eu/gmic325/img/v_menger_sponge.mp4) _Fig. 4.3.2. Vidéo d’une éponge de Menger, rendue par G’MIC._


- La commande [`chainring3d`](https://gmic.eu/reference/chainring3d) produit un anneau 3D de tores colorés :


[![chainring3d](https://gmic.eu/gmic325/img/v_chainring3d.gif)](https://gmic.eu/gmic325/img/v_chainring3d.gif) _Fig. 4.3.3. Rendu d’un anneau 3D de tores colorés, avec la commande `chainring3d`._


- La commande [`curve3d`](https://gmic.eu/reference/curve3d) génère le maillage 3D d’une courbe paramétrée `t → (x(t),y(t),z(t))` avec optionnellement une épaisseur de rayon `r(t)`, elle aussi paramétrée.


[![curve3d](https://gmic.eu/gmic325/img/v_curve3d.gif)](https://gmic.eu/gmic325/img/v_curve3d_2.mp4) _Fig. 4.3.4. Rendu d’une courbe 3D paramétrée, créé par la commande `curve3d`._


- La commande [`sphere3d`]((https://gmic.eu/reference/sphere3d)) peut maintenant produire des maillages 3D de sphères par trois méthodes différentes : 1. la subdivision d’isocahèdres, 2. la subdivision de cubes, et 3. la discrétisation angulaire en coordonnées sphériques. Les voici illustrées de gauche à droite, ci-dessous :


[![sphere3d](https://gmic.eu/gmic325/thumbs/sphere3d.png)](https://gmic.eu/gmic325/img/sphere3d.jpg) _Fig. 4.3.5. Production de maillages 3D de sphères, avec trois algorithmes de maillage différents, via la commande `sphere3d`._


En pratique, toutes ces nouvelles commandes de création de maillages 3D peuvent s’insérer dans des _pipelines_ _G’MIC_ plus complexes, afin de construire des objets 3D sophistiqués de manière procédurale. Ces maillages pourront ensuite être exportés en fichier `.obj`. En voici l’illustration, avec la création d’un anneau de chaines récursif qui a été d’abord généré par _G’MIC_ (utilisant d’ailleurs la commande `chainring3d` comme élément de base), puis importé dans [_Blender_](https://www.blender.org) :


[![antoine3d](https://gmic.eu/gmic325/thumbs/antoine3d_blender.png)](https://gmic.eu/gmic325/img/antoine3d_blender.jpg) _Fig. 4.3.6. Génération procédurale d’objet faite en G’MIC, puis importé dans Blender._


# 5. Autres nouveautés


Cette dernière section livre quelques autres informations liées au projet, sans ordre précis.


## 5.1. Amélioration diverses du greffon G’MIC-Qt


Beaucoup de travail a été accompli sur le code du greffon _G’MIC-Qt_, même si cela n’est pas forcément visible au premier abord. Citons en particulier :


- Des **optimisations importantes** du code qui améliorent le temps de démarrage du greffon : la fenêtre du greffon s’affiche plus rapidement, l’analyseur des filtres est plus efficace, notamment grâce à l’utilisation d’un cache binaire stockant les informations des filtres analysés après une mise à jour.
- Des **améliorations** concernant la **stabilité** du greffon. Il gère mieux les _threads_ lancés par des filtres non terminés.
- Un changement du thème de l’interface, qui passe par défaut **en mode sombre** (« _Dark Mode_ »).
- Le temps d’exécution d’un filtre apparaît maintenant lorsque l’on clique sur le bouton « _Apply_ ».
- Un nouveau système de gestion des **sources externes de filtres** : il devient facile pour un développeur de partager ses filtres _G’MIC_ personnalisés avec un utilisateur, en lui fournissant un fichier ou une URL pointant vers leur implémentation (à la manière des _[PPA](https://doc.ubuntu-fr.org/ppa)_ pour les gestionnaires de paquets sous _Ubuntu_).


[![filter_sources](https://gmic.eu/gmic325/thumbs/filter_sources.png)](https://gmic.eu/gmic325/img/filter_sources.jpg) _Fig. 5.1.1. Le nouveau système de gestion des sources de filtres externes dans le greffon _G’MIC-Qt_._


- Le greffon offre un moyen aux filtres de conserver des données persistantes dans un cache en mémoire, lors d’appels consécutifs. Cela permet aux filtres ayant besoin de charger ou générer des données volumineuses, de ne le faire qu’une fois, et de les réutiliser lors des appels suivants. Ce système est par exemple utilisé par le filtre **Rendering / 3D Mesh** pour stocker l’objet 3D lu à partir d’un fichier.
- Le code du greffon a été modifié pour faciliter un future portage vers la version 6 de la bibliothèque _Qt_.
- Grâce au travail de [Nicholas Hayes](https://github.com/0xC0000054), le greffon _G’MIC-Qt_ est maintenant disponible sur le [_Marketplace_ d’_Adobe_](https://exchange.adobe.com/apps/cc/109191/gmic). L’installation du greffon est donc maintenant facilitée pour les utilisateurs de [Photoshop](https://fr.wikipedia.org/wiki/Adobe_Photoshop).

- Mentionnons enfin la mise à jour du greffon pour la dernière version de [Digikam](https://www.digikam.org/) (la _8.0.0_), grâce au travail de [Gilles Caulier](https://invent.kde.org/cgilles). Une [documentation fournie](https://docs.digikam.org/en/image_editor/enhancement_tools.html#g-mic-qt-tool) a été mise en ligne sur le site de _Digikam_.


[![digikam](https://gmic.eu/gmic325/thumbs/digikam.png)](https://gmic.eu/gmic325/img/digikam.jpg) _Fig. 5.1.2. Le greffon G’MIC-Qt est disponible directement depuis Digikam, logiciel libre de gestion de photographies._


## 5.2. Amélioration de la bibliothèque standard `stdgmic`


La bibliothèque standard de _G’MIC_ ([`stdgmic`](https://raw.githubusercontent.com/GreycLab/gmic/develop/src/gmic_stdlib.gmic)) contient l’ensemble des commandes non natives, écrites directement en langage _G’MIC_, et distribuées par défaut avec le cadriciel. En pratique, la grand majorité des commandes existantes rentrent dans ce cadre. En plus des nouvelles commandes déjà décrites plus haut, notons les ajouts et améliorations suivantes dans la `stdgmic` :


- La bibliothèque `nn_lib`, permettant l’**apprentissage de réseaux de neurones** simples, se dote de nouveaux modules (_Softmax Layer_, _Cross-Entropy Loss_, _Binary Cross-Entropy Loss_, _Conv3D_, _Maxpool3D_ et _PatchUp/PatchDown 2D/3D_). Son développement avance doucement. Elle est déjà utilisée par le filtre **Repair / Denoise**, [déjà mentionné](https://linuxfr.org/news/sortie-de-g-mic-3-0-une-troisieme-dose-pour-un-traitement-efficace-de-vos-images#toc-22-am%C3%A9lioration-dimages) dans notre précédente dépêche. Nous avons aussi implémenté quelques exemples « jouets » d’apprentissage statistique utilisant cette bibliothèque, comme par exemple l’apprentissage d’une fonction _(x,y) → (R,G,B)_ représentant une image. L’idée ici est d’apprendre à un réseau de neurones à reproduire une image couleur, en lui fournissant comme données d’apprentissage les coordonnées _(x,y)_ des points de l’image (en entrée) et leurs couleurs _(R,G,B)_ correspondantes (en sortie). La figure ci-dessous montre l’image globale reconstruite par le réseau au fur et à mesure des itérations d’apprentissage :


[![nnlib](https://gmic.eu/gmic325/thumbs/nnlib_xytorgb.png)](https://gmic.eu/gmic325/img/nnlib_xytorgb.jpg) _Fig. 5.2.1. Apprentissage par réseaux de neurones d’une fonction (x,y) → (R,G,B) représentant une image. Les différentes itérations du processus d’apprentissage sont affichées._


La séquence d’apprentissage complète est visible dans la vidéo ci-dessous :


[![v_nnlib](https://gmic.eu/gmic325/thumbs/v_nnlib_xytorgb.png)](https://gmic.eu/gmic325/img/v_nnlib_xytorgb.mp4) _Fig. 5.2.2. Séquence des itérations d’apprentissage du réseau de neurones, pour l’apprentissage d’une fonction (x,y) → (R,G,B) représentant une image._


Nous avons également des exemples fonctionnels de la `nn_lib` pour classifier automatiquement des images simples (provenant entre autres des jeux de données [_MNIST_](http://yann.lecun.com/exdb/mnist/) et [_Fashion MNIST_](https://github.com/zalandoresearch/fashion-mnist)). _G’MIC_ peut donc potentiellement détecter le contenu de certaines images, comme illustré ci dessous avec la classification de chiffres manuscrits (nous avons en stock une méthode similaire pour la détection de visages humains).


[![mnist](https://gmic.eu/gmic325/thumbs/mnist.png)](https://gmic.eu/gmic325/img/mnist.jpg) _Fig. 5.2.3. Classification automatique d’images de chiffres manuscrits (base de données _MNIST_) par réseau de neurones, via l’utilisation de la bibliothèque `nn_lib` de G’MIC_.


Un début de documentation sur l’utilisation de cette bibliothèque d’apprentissage statistique en langage _G’MIC_ est disponible sur [notre forum de discussion](https://discuss.pixls.us/t/neural-networks-in-gmic-an-introduction-to-the-api-of-nn-lib/33536).


- Autre fonctionnalité de la `stdgmic` : la commande [`match_icp`](https://gmic.eu/reference/match_icp) implémente l’algorithme appelé « [Iterative Closest Point](https://fr.wikipedia.org/wiki/Iterative_Closest_Point) » (_ICP_), qui met en correspondance deux ensembles de vecteurs à _N_ dimensions. Cette commande peut servir à déterminer la transformation géométrique rigide (rotation + translation) entre deux _frames_ d’une animation, et cela, même en présence de bruit. L’animation ci-dessous illustre ce processus, avec deux transformations rigides estimées par _ICP_, pour recaler respectivement les silhouettes d’étoile et de coeur.


[![lineaa](https://gmic.eu/gmic325/img/v_icp.gif)](https://gmic.eu/gmic325/img/v_icp.gif) _Fig. 5.2.4. Recalage de silhouettes par algorithme d’« Iterative Closest Point », via la commande `match_icp`._


- Signalons aussi les nouvelles commandes [`img2patches`](https://gmic.eu/reference/img2patches) et [`patches2img`](https://gmic.eu/reference/patches2img) :
elles permettent respectivement la décomposition d’une image en un empilement volumique d’imagettes (« _patchs_ ») et sa récomposition, éventuellement en prenant en compte des _patchs_ qui se superposent. Par exemple, la commande :


```sh
$ gmic butterfly.jpg img2patches 64
```





va transformer l’image d’entrée (à gauche ci-dessous) en un empilement volumique de _patchs_ (image de droite) :


[![img2patches0](https://gmic.eu/gmic325/thumbs/img2patches0.png)](https://gmic.eu/gmic325/img/img2patches0.jpg) _Fig. 5.2.5. Transformation d’une image couleur en un empilement volumique de _patchs_, par la commande `img2patches`._


On peut ensuite traiter cet ensemble de _patchs_, par exemple en les triant dans l’ordre croissant de leur variance (donc du niveau de détails qu’ils contiennent), avant de recomposer l’image. Comme avec la commande suivante :


```sh
$ gmic sample butterfly W,H:=w,h img2patches 64,0,3 split z sort_list +,iv append z patches2img '$W,$H'
```





Ceci produit l’image ci-dessous, où les _patchs_ sont de plus en plus détaillés au fur et à mesure que l’on descend dans l’image.


[![img2patches](https://gmic.eu/gmic325/thumbs/img2patches.png)](https://gmic.eu/gmic325/img/img2patches.jpg) _Fig. 5.2.6. Tri des patchs d’une image par ordre de détail croissant._


- La nouvelle commande [`line_aa`](https://gmic.eu/reference/line_aa), implémente l’algorithme de [Xiaolin Wu](https://fr.wikipedia.org/wiki/Algorithme_de_trac%C3%A9_de_segment_de_Xiaolin_Wu) pour le tracé de segments [_anti-aliasées_](https://fr.wikipedia.org/wiki/Anticr%C3%A9nelage), c’est-à-dire qu’elle essaye de minimiser l’effet de crénelage qui apparaît classiquement lors du tracé de primitives dans des images discrètes.


[![lineaa](https://gmic.eu/gmic325/thumbs/lineaa.png)](https://gmic.eu/gmic325/img/lineaa.jpg) _Fig. 5.2.7. Comparaison des rendus de tracés de segments, entre l’algorithme classique de Brensenham et l’algorithme de Xiaolin Wu implémenté par la commande `line_aa`._


- Pour achever cette section sur la bibliothèque standard de _G’MIC_, mentionnons l’arrivée des commandes [`ssim`](https://gmic.eu/reference/ssim) (calcul de la mesure « _[Structural Similarity](https://fr.wikipedia.org/wiki/Structural_Similarity)_ » entre deux images), [`opening`](https://gmic.eu/reference/opening), [`opening_circ`](https://gmic.eu/reference/opening_circ), [`closing`](https://gmic.eu/reference/closing), [`closing_circ`](https://gmic.eu/reference/closing_circ) (ouverture et fermeture morphologiques avec élément structurant carré ou circulaire), [`betti`](https://gmic.eu/reference/betti) (calcul des [nombres de _Betti_](https://fr.wikipedia.org/wiki/Nombre_de_Betti), invariants topologiques de formes discrétisées en 2D ou 3D) et d’un nouveau mode de fusion de calque `shapeprevalent` pour la commande [`blend`](https://gmic.eu/reference/blend). Comme vous le voyez, il y a toujours de nouvelles choses à explorer ☺ !


## 5.3. Informations diverses liées au projet


Pour terminer cette longue dépêche, voici en vrac, quelques informations générales sur le projet _G’MIC_.


- D’abord, un rappel de l’existence de greffons [_OpenFX_](https://en.wikipedia.org/wiki/OpenFX_(API)) embarquant les fonctionnalités de _G’MIC_, permettant donc d’appliquer la plupart de nos filtres dans les logiciels d’édition vidéo qui implémentent cette _API_ (tels que [_Natron_](https://fr.wikipedia.org/wiki/Natron_(logiciel)) ou [_Adobe After Effects_](https://fr.wikipedia.org/wiki/Adobe_After_Effects)). Pour en savoir plus, voir [le _post_ dédié](https://discuss.pixls.us/t/gmic-for-openfx-and-adobe-plugins) de l’auteur de ces greffons, [Tobias Fleischer](https://discuss.pixls.us/u/tobias_fleischer/).


[![openfx](https://gmic.eu/gmic325/thumbs/after_effect.png)](https://gmic.eu/gmic325/img/after_effect.jpg) _Fig. 5.3.1. Un des greffons OpenFX de G’MIC en action, dans le logiciel Adobe After Effects._


[![openfx2](https://gmic.eu/gmic325/thumbs/natron.png)](https://gmic.eu/gmic325/img/natron.jpg) _Fig. 5.3.2. Un des greffons OpenFX de G’MIC en action, dans le logiciel Natron._


- Notre algorithme d’[éclairage automatique de dessins colorisés en aplats](https://linuxfr.org/news/g-mic-2-3-4-traiter-ses-images-en-se-disant-deja-10-ans#toc-2-illumination-automatique-de-dessins-coloris%C3%A9s-en-aplats), mentionné lors d’une dépêche précédente (filtre **Illuminate 2D Shape**) a fait l’objet d’une publication en fin d’année 2022, à la conférence [_IEEE International Conference on Image Processing_](https://2022.ieeeicip.org/) à Bordeaux. Cette publication, intitulée « _[Automatic Illumination of Flat-Colored Drawings by 3D Augmentation of 2D Silhouettes](https://tschumperle.users.greyc.fr/publications/tschumperle_icip22.pdf)_ » détaille l’ensemble de l’algorithme implémenté dans ce filtre. Ce filtre est apprécié des illustrateurs, qui peuvent l’utiliser pour donner rapidement du relief à leurs dessins colorisés en aplats, comme le montre la vidéo suivante :


[![illuminate_shape](https://gmic.eu/gmic325/thumbs/youtube_illuminate2d_shape.png)](https://www.youtube.com/watch?v=WQ2u639FgyQ) _Fig. 5.3.3. Tutoriel vidéo d’utilisation du filtre **Illuminate 2D Shape** pour l’éclairage automatique d’un dessin colorisé en aplats._


Les plus curieux de détails techniques sur l’algorithme pourront visualiser la présentation suivante, donnée à la conférence _ICIP’2022_ :


[![illuminate_shape2](https://gmic.eu/gmic325/thumbs/youtube_illuminate2d_shape_icip.png)](https://www.youtube.com/watch?v=PmWlan_8Qdo) _Fig. 5.3.4. Vidéo d’explication de l’algorithme à la base du filtre **Illuminate 2D Shape**._


- Notons que le langage de script de _G’MIC_ est suffisamment flexible pour être utilisé, non seulement pour définir des filtres de traitement d’images, mais aussi pour élaborer des **démonstrateurs interactifs**. Au laboratoire _GREYC_, il nous a permis de développer deux bornes de démonstration autour du traitement d’images. Ces démonstrateurs sont exposés sur notre stand lors d’évènements grand-public (par exemple la [Fête de la Science](https://www.fetedelascience.fr/), ou le [Festival de l’Excellence Normande](https://www.normandie-tourisme.fr/evenement/feno-festival-excellence-normande/)).


Le premier de ces démonstrateurs est visible en cliquant sur l’image ci-dessous (présentation donnée par notre collègue [Loïc Simon](https://simonl02.users.greyc.fr/)). Il illustre la problématique du « _transfert de style_ » entre deux images. Il s’exécute sur une table tactile.


[![demo_table_tactile](https://gmic.eu/gmic325/thumbs/demo_table_tactile.png)](https://www.vip-studio360.fr/galerie360/visites/vv-ensicaen/vv-ensicaen-2022-c.html?s=pano41&h=0&v=0.0000&f=90.0000&skipintro&norotation) _Fig. 5.3.5. Aperçu du démonstrateur G’MIC de transfert de style (cliquez sur l’image pour accéder à la démo à 360°)._


Le deuxième démonstrateur permet de jouer avec un miroir déformant interactif, comme montré dans la vidéo ci-dessous :


[![greyc_warp](https://gmic.eu/gmic325/thumbs/v_greyc_warp.png)](https://gmic.eu/gmic325/img/v_greyc_warp.mp4) _Fig. 5.3.6. Démonstrateur interactif de déformation d’images, implémenté en langage G’MIC._


- À titre de projet personnel, j’ai commencé l’écriture d’un [_raytracer_](https://fr.wikipedia.org/wiki/Ray_tracing) simple en langage _G’MIC_, pour tester les capacités du langage. Le but n’est pas forcément d’aller très loin (par manque de temps, car c’est très intéressant en pratique !), mais c’est un bon moyen de détecter les optimisations intéressantes qui pourraient être faites dans l’interpréteur _G’MIC_ ultérieurement. Une animation d’un objet simple, générée par ce _raytracer_ en cours de développemnt, est visible ci-dessous :


[![raytracer](https://gmic.eu/gmic325/thumbs/v_raytracer.png)](https://gmic.eu/gmic325/img/v_raytracer.mp4) _Fig. 5.3.7. Exemple de rendu obtenu par la technique du raytracing, implémentée en G’MIC (en cours de développement)._


- Pour ceux qui veulent en savoir plus sur le fonctionnement du langage _G’MIC_, nous recommandons la lecture des [formidables pages de tutoriel](https://gmic.eu/tutorial/) écrites par [Garry Osgood](https://discuss.pixls.us/u/grosgood), contributeur depuis plusieurs années à la documentation du projet _G’MIC_. En particulier, il a récemment écrit [une série d’articles sur la création d’arabesques](https://gmic.eu/tutorial/wheelies.html), que l’on ne peut que conseiller !

[![arabesque](https://gmic.eu/gmic325/thumbs/v_arabesque.png)](https://gmic.eu/gmic325/img/v_arabesque.mp4) _Fig. 5.3.8. Exemple de tracé de silhouette par la technique d’arabesque décrite dans le tutoriel de Garry Osgood._


- Notons qu’avec le langage _G’MIC_, il est aussi possible de créer des [_one-liners_](https://fr.wiktionary.org/wiki/one-liner) amusants, c’est-à-dire des commandes qui tiennent sur une ligne et qui génèrent des images ou des animations insolites. Les deux commandes _G’MIC_ suivantes en sont de bons exemples :


**One-liner N°1** : Génération d’une image couleur fixe.


```sh
$ gmic 500,500 repeat 10 { +noise_poissondisk[0] '{3+$>}' } rm[0] a z f '!z?(R=cut(norm(x-w/2,y-h/2)/20,0,d-1);i(x,y,R)):0' slices 0 to_rgb f 'max(I)?u([255,255,255]):I' blur_radial 0.6% equalize n 0,255
```





[![lightspeed](https://gmic.eu/gmic325/thumbs/lightspeed.png)](https://gmic.eu/gmic325/img/lightspeed.jpg) _Fig.5.3.9. Résultat du one-liner N°1._


**One-liner N°2 :** Création d’une animation couleur, de type « peau de dinosaure ».


```sh
$ gmic 300,300x5 foreach { noise_poissondisk 40 +distance 1 label_fg.. 0 mul. -1 watershed.. . rm. g xy,1 a c norm neq 0 distance 1 apply_gamma 1.5 n 0,255 } morph 20,0.1 map copper +rv[^0] animate 40
```





[![reptile_skin](https://gmic.eu/gmic325/img/v_reptile_skin.gif)](https://gmic.eu/gmic325/img/v_reptile_skin.gif) _Fig.5.3.10. Résultat du one-liner N°2._


- Les deux images ci-dessous sont le résultat d’expérimentations en langage _G’MIC_ de [_Reptorian_](https://discuss.pixls.us/u/reptorian), contributeur de longue date, qui explore beaucoup les possibilités du langage pour l’art génératif.


[![generative_art2](https://gmic.eu/gmic325/thumbs/ga_reptorian_da2.png)](https://gmic.eu/gmic325/img/ga_reptorian_da2.jpg) _Fig.5.3.11. Variante de la technique de « _[Diffusion-limited aggregation](https://en.wikipedia.org/wiki/Diffusion-limited_aggregation)_ », guidée par la géométrie d’une image (par Reptorian)._


[![generative_art3](https://gmic.eu/gmic325/thumbs/ga_reptorian.png)](https://gmic.eu/gmic325/img/ga_reptorian.jpg) _Fig.5.3.12. Génération de motif fractal (par Reptorian)._


D’autres exemples sont visibles sur [son fil de discussion](https://discuss.pixls.us/t/gmic-fun-with-reptorian/) (en anglais).


- Concernant la dimension « communication » du projet, il existe depuis plusieurs années un [compte _Twitter_](https://twitter.com/gmic_eu) où nous postons régulièrement des informations sur l’évolution du projet, l’arrivée de nouvelles fonctionnalités, la sortie de nouvelles versions, etc. Dorénavant, nous avons également [un compte _Mastodon_](https://piaille.fr/@gmic), où nous postons les actualités autour du projet. N’hésitez pas à vous y abonner !


[![mastodon](https://gmic.eu/gmic325/thumbs/mastodon.png)](https://piaille.fr/@gmic) _Fig. 5.3.13. Aperçu du compte Mastodon de G’MIC._


- Sur les réseaux sociaux, il arrive qu’on tombe sur des _posts_ inattendus où des personnes montrent leur utilisation de _G’MIC_. Par exemple, cette série de _posts_ récents met en jeu du traitement d’images astronomiques avec des filtres de _G’MIC_, pour débruiter ou esthétiser des images :


[![astro](https://gmic.eu/gmic325/thumbs/astro.png)](https://gmic.eu/gmic325/img/astro.jpg) _Fig. 5.3.14. Utilisation de G’MIC pour le traitement d’images astronomiques._


Ces _posts_ sont visibles [ici](https://twitter.com/navaneeth_ank/status/1620110820272410624), [là](https://twitter.com/SpaceGeck/status/1594213385377574913), [là](https://twitter.com/stim3on/status/1594292010000814080), ou [encore là](https://twitter.com/navaneeth_ank/status/1659381911255654400). Ces retours d’utilisateurs sont évidemment valorisants pour nous. Si vous êtes vous même utilisateurs (contents ☺) de _G’MIC_, n’hésitez surtout pas à partager vos réalisations ou vos retours d’expérience. Ca fait toujours plaisir !


- Enfin, mentionnons le fait que _G’MIC_ a fait l’objet d’articles dans les numéros _301_ et _302_ du magazine anglais [LinuxFormat](https://www.linuxformat.com/) (numéros de mai et juin 2023), rédigés par [Karsten Gunther](https://linuxformat.com/archives?author_find=217). Ils présentent les différentes possibilités de retouche photo apportées par le greffon _G’MIC-Qt_, d’une manière très pédagogique (comme nous essayons d’ailleurs de le faire avec nos dépêches sur [_Linuxfr_](https://linuxfr.org/tags/gmic/public) !).


[![linux_format](https://gmic.eu/gmic325/thumbs/linux_format.png)](https://gmic.eu/gmic325/img/linux_format.jpg) _Fig. 5.3.15. Le magazine « Linux Format » propose une série d’articles sur l’utilisation de G’MIC-Qt, dans ses numéros de mai et juin 2023._


Voilà, ce qui conclut notre tour d’horizon des derniers développements et informations portant sur le projet _G’MIC_.


# 6. Conclusions & perspectives


Après **15 ans** de développement de _G’MIC_ et **24 ans** de développement de [_CImg_](http://cimg.eu), la bibliothèque _C++_ qui lui sert de fondation, nous disposons aujourd’hui d’un cadriciel libre et ouvert pour le traitement des images numériques, qui est mature et qui a prouvé son utilité pour résoudre des problèmes variés de traitement d’images.
Le nombre de téléchargements n’a cessé de croître, depuis l’écriture des premières lignes de code (en 2008), ce qui montre que le projet est dynamique et attire un large éventail d’utilisateurs.

Ce dynamisme est il durable ? Nous avons bien sûr toujours des idées pour l’amélioration de ce cadriciel. Mais en même temps, avec les responsabilités professionnelles qui augmentent, le temps à consacrer à son développement diminue. La stratégie pour la suite sera donc de :


- Bien sélectionner les pistes d’amélioration sur lesquelles travailler.
- Tenter de trouver du temps de développement extérieur (soit bénévole, soit financé).


Sur le court-terme, nous sommes à la recherche de contributeurs pour :


  - Avancer sur le développement du [_binding_ _G’MIC_](https://pypi.org/project/gmic/) pour [_Python_](https://www.python.org/). Il faudrait le mettre à jour et consacrer suffisamment de temps à le tester en profondeur, pour rendre _G’MIC_ utilisable sans _bugs_, directement depuis un programme écrit en _Python_. Le _binding_ existant est fonctionnel et constitue déjà une bonne base de travail.
  - Réussir à _packager_ _G’MIC_ pour [_macOS_](https://fr.wikipedia.org/wiki/MacOS). Nous recevons en effet de nombreuses requêtes d’utilisateurs de _Mac_ qui ne savent pas compiler et installer le greffon _G’MIC-Qt_ pour _GIMP_. Nul doute qu’il soit possible d’améliorer cette situation, moyennant de l’aide extérieure.


Si vous pensez pouvoir contribuer sur l’un de ces deux points, [n’hésitez surtout pas à nous contacter !](https://discuss.pixls.us/c/software/gmic)


Enfin, la révolution induite par l’utilisation des réseaux de neurones dans le domaine du traitement des images numériques est primordiale. Sur ce point, _G’MIC_ a du retard à rattraper. Nous nous sommes plutôt focalisés jusqu’à présent sur l’algorithmique « classique » du traitement d’images. Il faudrait pouvoir développer plus rapidement notre bibliothèque `nn_lib` pour parvenir à déployer des modèles neuronaux plus larges (quelques dizaines/centaines de millions de paramètres, ça serait déjà satisfaisant !), afin d’autoriser le traitement ou la synthèse d’images en utilisant des techniques plus avancées d’apprentissage statistique.


Comme vous le voyez, ce ne sont pas les idées qui manquent !


Pour finir, il faut rappeler que le développement de _G’MIC_ n’aurait pas été possible sans les encouragements et le support du [_GREYC_](https://www.greyc.fr/), notre laboratoire, et de ses tutelles : l’[Institut INS2I du CNRS](https://www.ins2i.cnrs.fr/fr), l’[Université de Caen Normandie](https://www.unicaen.fr/), et l’[_ENSICAEN_](https://www.ensicaen.fr/). Un grand merci à eux pour leurs aides à différents niveaux lors de ces quinze dernières années de développement. Depuis quelques temps, on voit se mettre en place, dans le domaine de la recherche scientifique, des initiatives intéressantes de valorisation de la science ouverte et reproductible ([plan national pour la science ouverte](https://www.ouvrirlascience.fr/deuxieme-plan-national-pour-la-science-ouverte-pnso/), plan de la [science ouverte du CNRS](https://www.science-ouverte.cnrs.fr/), …), et du logiciel libre (programme de valorisation [Open de CNRS Innovation](https://www.cnrsinnovation.com/open/)). Ce sont des signaux encourageants pour les chercheurs qui investissent souvent beaucoup de temps dans la création de communs numériques libres (logiciels, jeux de données, etc.), et qui ont parfois du mal à valoriser ces réalisations comme des contributions scientifiques d’importance.


Nous espérons que cette dépêche vous a plu. Rendez vous dans quelques ~~mois~~ semestres, avec, on l’espère, encore de nombreuses nouveautés à partager avec vous !
