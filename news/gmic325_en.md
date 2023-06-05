# G’MIC 3.2.5: 15 years of development for open and reproducible image processing

To celebrate the release of version **3.2.5** of [_G’MIC_](https://gmic.eu) (_GREYC’s Magic for Image Computing_), an open [framework](https://en.wikipedia.org/wiki/Software_framework) for [digital image processing](https://en.wikipedia.org/wiki/Digital_image_processing), we present you with a summary of the new features implemented since our [previous report](https://linuxfr.org/news/sortie-de-g-mic-3-0-une-troisieme-dose-pour-un-traitement-efficace-de-vos-images) (published during December of 2021). It is also the opportunity for us to celebrate the project's **15 years** of existence!

_G’MIC_ is being developed in [Caen](https://en.wikipedia.org/wiki/Caen), in France, by the [_IMAGE_](https://www.greyc.fr/image) team  of [_GREYC_](https://www.greyc.fr), a public research lab in Information and Communication Sciences and Technologies (Joint Research Unit [_CNRS_](https://www.cnrs.fr/) / [_ENSICAEN_](https://www.ensicaen.fr/) / [Université de Caen](https://www.unicaen.fr/)). It is distributed under the free [_CeCILL_](http://www.cecill.info/licences/Licence_CeCILL_V2.1-en.html) licence.

[![gmic_teaser](https://gmic.eu/gmic325/thumbs/greyc.png)](https://gmic.eu/gmic325/img/greyc.jpg)

In this report, we will explain in detail a few of the recently added features, and illustrate them with examples of 2D and 3D image processing and synthesis.

_A. N. : Click on images to see a full resolution version, or a link to the video for images showing the icon_ 

===
![play video](https://gmic.eu/gmic325/thumbs/icon_play_video.png)
===
---

* [The G’MIC project](https://gmic.eu)
* [The Project's Mastodon news feed](https://piaille.fr/@gmic)
* [Série d’articles G’MIC sur LinuxFr.org](https://linuxfr.org/tags/gmic/public)

---

# 1. What is _G’MIC_ ?

[_G’MIC_](https://gmic.eu) is an open [digital image](https://en.wikipedia.org/wiki/Digital_image) manipulation and processing framework. It provides various user interfaces allowing algorithmic manipulation of images and signals. The heart of this project is based on the implementation of a scripting language (the [_« G’MIC language »_](https://gmic.eu/reference/overall_context.html)), specifically designed to ease the prototyping and implementation of new image processing algorithms and operators. Users can apply operators among several hundreds already available, but they also have the capability of writing their own processing pipelines and making them available through the various user interfaces of the project. It is therefore, in essence, an open, expandable and constantly evolving framework.

_G’MIC_ 's most accomplished user interfaces are: [`gmic`](https://gmic.eu/reference/), the command line interface (useful addition to [_ImageMagick_](https://www.imagemagick.org/) or [_GraphicsMagick_](http://www.graphicsmagick.org) for people who like to use the terminal), the Web service [_G’MIC Online_](https://gmicol.greyc.fr/), and above all, the plug-in [_G’MIC-Qt_](https://github.com/c-koi/gmic-qt), which can be used in numerous popular image editing software such as [_GIMP_](https://www.gimp.org), [_Krita_](https://www.krita.org), [_DigiKam_](https://www.digikam.org), [_Paint.net_](https://www.getpaint.net), [_Adobe Photoshop_](https://en.wikipedia.org/wiki/Adobe_Photoshop), [_Affinity Photo_](https://en.wikipedia.org/wiki/Affinity_Photo)… This plug-in is very easy to use and now provides more than **580 processing filters** to augment these image manipulation programs.

===
[![Greffon G’MIC-Qt](https://gmic.eu/gmic325/thumbs/gmic_qt_325.png)](https://gmic.eu/gmic325/img/gmic_qt_325.jpg)
_Fig. 1.1. Preview of the G’MIC-Qt plug-in, in version ***3.2.5*** , here launched from GIMP 2.10._
===

Thanks to its dedicated scripting language, new filters and effects are regularly added to _G’MIC_.

In this article, we will describe a few of these new filter effects and give some news about the project. We will also show some examples for the `gmic` command line tool, which is by far the most powerful interface provided by the project.

# 2. New abstraction, _Glitch Art_ and pattern generation filters

- To begin this new features report, let's mention the existence of a new transformation filter which converts images to [Line Art](https://en.wikipedia.org/wiki/Line_art) drawings. This filter, appropriately named **Artistic / Line Art** was conceived by [Claude Lion](https://github.com/cl4cnam), an external contributor who is already the author of multiple filters (such as the very appreciated **Artistic / Comic Book**, [already mentioned](https://gmic.eu/gmic300/#_2_1_artistic_effects) in our previous article.

This filter analyses the geometry of the main structures in images and decides if these structures should appear in a picture redrawn on a white background, either as black lines or as gray or black filled regions. It is particularly effective on portraits, since the contrasts are rather well marked marked in this type of images.

===
[![filter lineart](https://gmic.eu/gmic325/thumbs/filter_lineart.png)](https://gmic.eu/gmic325/img/filter_lineart.jpg)
_Fig. 2.1. The ***Artistic / Line Art*** filter, as seen in the G’MIC-Qt plug-in._
===

The interactive preview of the _G’MIC-Qt_ plug-in alleviates the adjustment of all the filter's settings to personalize the expected results. Pressing either the « _Apply_ » or « _OK_ » button applies the filter to the picture. Note that once these settings are selected, pressing the « _Copy to Clipboard_ » button in the plug-in's interface will copy the corresponding _G’MIC_ command to the clipboard.

===
[![filter lineart zoom](https://gmic.eu/gmic325/thumbs/filter_lineart_zoom.png)](https://gmic.eu/gmic325/img/filter_lineart_zoom.jpg)
_Fig. 2.2. The « Copy to Clipboard » button adds the G'MIC command corresponding to the filter's action to the clipboard._
===

Then, to apply the effect with the same parameters on different images (for batch processing), all you need is to launch `gmic` in a terminal, add the filename of the image to process, followed by the command previously copied to the clipboard, which will give something like this:

~~~
$ gmic autre_portrait.jpg cl_lineart 0,0,2,1,15,15,1,0,6,2,2,0,0,0,50,50 output lineart.png
~~~

This method is useful when one wants to use certain _G’MIC_ effects inside personalized scripts (this obviously works with all the filters available in the plug-in).

===
[![lineart](https://gmic.eu/gmic325/thumbs/lineart.png)](https://gmic.eu/gmic325/img/lineart.jpg)
_Fig. 2.3. The « Line Art » filter, applied on another portrait image, with the same settings, from the terminal._
===

===
[![lineart](https://gmic.eu/gmic325/thumbs/lineart2.png)](https://gmic.eu/gmic325/img/lineart2.jpg)
_Fig. 2.4. The « Line Art » filter, applied on a few other example images._
===

- Now, let's take a look at the **Degradations / Huffman Glitches** filter, a fun way to generate [_Glitch Art_](https://en.wikipedia.org/wiki/Glitch_art). More precisely, here we will simulate image decompression artifacts with the deliberate addition of errors (bits inversion) in the [Huffman codes](https://en.wikipedia.org/wiki/Huffman_coding) which would have been used for the lossless compression of the input picture's data. This produces visible digital distortions on the picture when the altered data is decompressed, distortions which actually are the effects sought by the _Glitch Art_ aficionados!

===
[![huffman glitches](https://gmic.eu/gmic325/thumbs/huffman_glitches.png)](https://gmic.eu/gmic325/img/huffman_glitches.jpg)
_Fig. 2.5. The ***Degradations / Huffman Glitches*** filter, as seen in the G’MIC-Qt plug-in._
===
https://gmic.eu/gmic325/img/v_huffman_glitches.mp4
This filter allows the generation of compression artifacts with variations: block by block, line by line, column by column, or on image data encoded in color spaces other than _RGB_. In the end, the diversity of anomalies it is possible to produce is quite large, as depicted on the following figure:

===
[![huffman glitches2](https://gmic.eu/gmic325/thumbs/huffman_glitches2.png)](https://gmic.eu/gmic325/img/huffman_glitches2.jpg)
_Fig. 2.6. A few variations of the ***Degradations / Huffman Glitches*** filter settings._
===

Here again, it is easy to retrieve the _G’MIC_ command corresponding to the filter's operation, use it in a script, and, for example, apply this effect on all the _frames_ of a video (click on the picture below to view the video):

===
[![v huffman glitches](https://gmic.eu/gmic325/thumbs/v_huffman_glitches.png)](https://gmic.eu/gmic325/img/v_huffman_glitches.mp4)
_Fig. 2.7. The ***Degradations / Huffman Glitches*** filter applied on the [Tears of Steel](https://en.wikipedia.org/wiki/Tears_of_Steel) video by the [Blender foundation](https://en.wikipedia.org/wiki/Blender_Foundation)._
===

There floats like the sweet scent of an analog TV set in the air...☺

- Let's also mention the appearance of a new filter, named **Patterns / Pack Ellipses**, which may not be entirely pleasing to our [trypophobic](https://en.wikipedia.org/wiki/Trypophobia) readers (not at all related to the phobia of eating "tripes à la mode de Caen" )! The goal of this filter is to redraw an image by fitting together colored ellipses, yet preventing them to touch each other. Ellipses are oriented parallel or orthogonal to the local structures, to make the most visible edges of images stick out. This is not the first filter of this kind in _G’MIC_, but here we have a new [sphere packing](https://en.wikipedia.org/wiki/Sphere_packing) algorithm, which executes quickly and produces interesting pictures.

===
[![pack ellipses](https://gmic.eu/gmic325/thumbs/pack_ellipses.png)](https://gmic.eu/gmic325/img/pack_ellipses.jpg)
_Fig. 2.8. The ***Patterns / Pack Ellipses*** filter, as seen in the G’MIC-Qt plug-in._
===

===
[![pack ellipses2](https://gmic.eu/gmic325/thumbs/ellipses.png)](https://gmic.eu/gmic325/img/ellipses.jpg)
_Fig. 2.9. Application of the ***Patterns / Pack Ellipses*** filter on different portrait images._
===

The video below is a step by step illustration of the algorithm's behaviour while fitting colored circles to reconstruct a portrait image:

===
[![v circle packing](https://gmic.eu/gmic325/thumbs/v_circle_packing.png)](https://gmic.eu/gmic325/img/v_circle_packing.mp4)
_Fig. 2.10. A video breakdown of the different steps of the ***Patterns / Pack Ellipses*** filter._
===

- Still among the textures and patterns generation effects, let's point out the appearance of a new [_Halftoning_](https://en.wikipedia.org/wiki/Halftone) filter, named **Patterns / Halftone [Generic]**. Here again, the idea is to reconstruct an input image by stacking small colored patterns of any shape, such as small circles for instance:

===
[![halftone generic](https://gmic.eu/gmic325/thumbs/halftone_generic.png)](https://gmic.eu/gmic325/img/halftone_generic.jpg)
_Fig. 2.11. The ***Patterns / Halftone [Generic]*** filter, as seen in the  G’MIC-Qt plug-in._
===

Or a spiral :

===
[![halftone generic2](https://gmic.eu/gmic325/thumbs/halftone_generic2.png)](https://gmic.eu/gmic325/img/halftone_generic2.jpg)
_Fig. 2.12. The ***Patterns / Halftone [Generic]*** filter with a spiral pattern._
===

The filter even provides a special mode so that the user can provide his own personalized _Halftoning_ pattern design on a separate layer:

===
[![halftone generic3](https://gmic.eu/gmic325/thumbs/halftone_generic3.png)](https://gmic.eu/gmic325/img/halftone_generic3.jpg)
_Fig. 2.13. The ***Patterns / Halftone [Generic]*** filter with a personalized pattern design._
===

From an algorithmic point of view, the idea is to locally erode or dilate the pattern passed as a filter parameter to best encode the grayscale value of each pixel of the input image.

- The following filter has an amusing story: subscribed to the _Twitter_ account of the artist [Memo Akten](https://www.memo.tv/), one day I stumbled upon [this tweet](https://twitter.com/memotv/status/1556619064491102209) describing a generative art algorithm that Memo imagined (but did not implement). It was a good opportunity to try to implement it in the _G’MIC_ language, just for the fun of experimenting!  Once it was done, creating a filter usable from the _G’MIC-Qt_ plug-in was self-evident. The result is the **Rendering / Algorithm A** filter, which creates « [Mondrian-like](https://en.wikipedia.org/wiki/Piet_Mondrian) » abstract illustrations.

===
[![algorithmA](https://gmic.eu/gmic325/thumbs/algorithmA.png)](https://gmic.eu/gmic325/img/algorithmA.jpg)
_Fig. 2.14. The filter Patterns / ***Algorithm A***, as seen in the G’MIC-Qt plug-in._
===

Image generation is largely based on drawing random numbers. From a simple command line, one can easily produce many different artworks in one go:

~~~
$ gmic repeat 6 { 500,500,1,3 fx_memoakten_algorithm_a[-1] '$>',20,30,30,2,50,10,50,40,3,60,1,0,0,0,255,255,255,255,0,0,255,128,0,255,255,0,0,0,0 } frame 1,1,0 frame 5,5,255 append_tiles 3 output output.png
~~~
which synthesizes the following image:

===
[![algorithmA2](https://gmic.eu/gmic325/thumbs/algorithmA2.png)](https://gmic.eu/gmic325/img/algorithmA2.jpg)
_Fig. 2.15. An « artworks » Patchwork produced by the ***Patterns / Algorithm A*** filter._
===

- Still in order to produce bizarre and abstract pictures, let's talk about the **Arrays & Tiles / Shuffle Patches** filter, which will break down an input image into a thumbnail array (« _patches_ »), then shuffle these _patches_ spatially before joining them to produce the resulting image. Different options are offered, allowing a random rotation of the _patches_, or reassembling overlapping _patches_.

===
[![shuffle_patches](https://gmic.eu/gmic325/thumbs/shuffle_patches.png)](https://gmic.eu/gmic325/img/shuffle_patches.jpg)
_Fig. 2.16. The ***Arrays & Tiles / Shuffle Patches filter,*** as seen in the G’MIC-Qt plug-in._
===

The result is an image resembling a patchwork of different parts of the original picture, with overall similar colors, but where the natural order of structures is lost.

===
[![shuffle_patches2](https://gmic.eu/gmic325/thumbs/shuffle_patches2.png)](https://gmic.eu/gmic325/img/shuffle_patches2.jpg)
_Fig. 2.17. Result of the ***Arrays & Tiles / Shuffle Patches*** filter applied to a landscape picture._
===

And again, we can apply this filter to all the _frames_ of a video, as illustrated in the example below (of course you will have recognized the short movie _[Big Buck Bunny](https://en.wikipedia.org/wiki/Big%5fBuck%5fBunny)_ by the [Blender Foundation](https://en.wikipedia.org/wiki/Blender%5fFoundation)).

===
 [![shuffle patches2](https://gmic.eu/gmic325/thumbs/v_shuffle_patches.png)](https://gmic.eu/gmic325/img/v%5fshuffle%5fpatches.mp4)
 _Fig. 2.18. The ***Arrays & Tiles / Shuffle Patches*** filter applied to the _[Big Buck Bunny](https://en.wikipedia.org/wiki/Big%5fBuck%5fBunny)_ video by the [Blender Foundation](https://en.wikipedia.org/wiki/Blender_Foundation))._
===

- And to close this section about image abstraction, _Glitch Art_ and pattern generation, here is the **Patterns / Pills** filter, which creates a periodic (repeating) texture resembling a stack of « pills » rotated 90° to each other.

===
[![pills](https://gmic.eu/gmic325/thumbs/pills.png)](https://gmic.eu/gmic325/img/pills.jpg)
_Fig. 2.19. The ***Patterns / Pills***, as seen in the G’MIC-Qt plug-in._
===

Nothing too complicated: this filter is a straight implementation of the folowwing mathematical formula:

===
[![pills_formula](https://gmic.eu/gmic325/thumbs/pills_formula.png)](https://gmic.eu/gmic325/img/pills_formula.jpg)
===

This nice formula was imagined by [Miloslav Číž](https://en.wikipedia.org/wiki/User:Drummyfish), and described on [this page](https://commons.wikimedia.org/wiki/File:2D_function_pills.png). It was tempting to create a new filter available to everyone!

Note that we can produce the same base image, directly from the original formula, once again by executing the `gmic` command line:

~~~
$ gmic 600,600,1,1,"X = x*30/w; Y = y*30/h; sqrt(abs(sin(X + cos(Y + sin(X + cos(Y)))) * sin(Y + cos(X + sin(Y + cos(X))))))" normalize 0,255
~~~

Nevertheless, the **Patterns / Pills** found in the _G’MIC-Qt_ plug-in allows some additional variations, like the possibility of specifying a rotation angle or independently creating these patterns for each _RGB_ channel of the output image.

# 3. Some news regarding color processing

## 3.1. _LUTs_ 3D features

_G’MIC_ is an image processing software natively integrating a lot of different [3D color_LUTs](https://en.wikipedia.org/wiki/3D_lookup_table), thanks, in particular, to an efficient _LUTs_ compression algorithm resulting from our research work (described [in a previous report](https://linuxfr.org/news/g-mic-2-7-0-une-rentree-pleine-de-style-pour-le-traitement-d-images#toc-4-toujours-plus-de-transformations-colorim%C3%A9triques)). These 3D color _LUTs_ define transformation functions of an image's colors, often to give it a specific ambiance. New commands to facilitate the visualization and creation of 3D color _LUTs_ were recently added to _G’MIC_:

- The [`display_clut`](https://gmic.eu/reference/display_clut) command renders a color _LUT_ in 3D, which allows to visualize the _RGB → RGB_ transformation it represents.

~~~
$ gmic clut summer clut spy29 display_clut 400 text_outline[0] Summer text_outline[1] "Spy 29"
~~~
will display:

===
[![display clut](https://gmic.eu/gmic325/thumbs/display_clut.png)](https://gmic.eu/gmic325/img/display%5fclut.jpg)
_Fig. 3.1.1. The `display_clut` command renders a color LUT in 3D._
===

- As for the [`random_clut`](https://gmic.eu/reference/random_clut) command, it creates a random 3D color _LUT_ preserving some properties of color continuity. For example, the following pipeline:

~~~
$ gmic sample colorful resize2dx 320 repeat 4 { random_clut +map_clut[0] [-1] display_clut[-2] 320 to_rgb[-2] append[-2,-1] y } frame 2,2,0 to_rgba append x,1
~~~

will synthesize an image like the one below:

===
[![random clut](https://gmic.eu/gmic325/thumbs/random_clut.png)](https://gmic.eu/gmic325/img/random_clut.jpg)
_Fig. 3.1.2. Multiple randomized 3D color ***LUTs*** obtained via the `random_clut` command, and applied to a color image._
===

## 3.2. New color filters for the _G'MIC-QT_ plug-in.

- Quite logically, the `random_clut` command is the basis for the implementation of the new **Colors / Random Color Transformation** filter, which was added to the _G’MIC-Qt_ plug-in and applies a random colorimetric transformation on an input image.

===
[![random color transformation](https://gmic.eu/gmic325/thumbs/random_color_transformation.png)](https://gmic.eu/gmic325/img/random_color_transformation.jpg)
_Fig. 3.2.1. The filter ***Colors / Random Color Transformation***, as seen in the G’MIC-Qt plug-in._
===

- To stay in the field of 3D color _LUTs_, let us mention the appearance of the filter **Colors / Apply From CLUT Set**, which allows transforming a color image by applying one of the 3D _LUT_ defined in a _pack_, itself stored in a `.gmz` file format.

Some explanations are needed:  the `.gmz` file format is implemented and used by _G'MIC_ for the serialization and backup of compressed generic binary data. Thus, how do we create a `.gmz` file storing a set of compressed 3D color _LUTs_, to supply the **Colors / Random Color Transformation** filter? Let's take the actual example of the _pack_ of 10 _LUTs_ generously offered [on this web page](https://www.editingcorp.com/free-hand-picked-luts-for-cinematic-color-grading/). These _LUTs_ are provided in `.cube` file format, the most common file type used for storing 3D color _LUTs_. This set of 10 files takes up **8.7 MB** on the drive.

===
[![clut set2](https://gmic.eu/gmic325/thumbs/clut_set2.png)](https://gmic.eu/gmic325/img/clut_set2.jpg)
_Fig. 3.2.2. visualization of the 10 3D color LUTs from our example case._
===

The following command line compresses them (with visually imperceptible loss) thanks to _G’MIC's_ _LUTs_ compression algorithm, to a [`clut_pack.gmz`](https://gmic.eu/gmic325/img/clut_pack.gmz) file weighting **156 KB**. Be careful, this compression process takes time (several tens of minutes)!

~~~
$ gmic *.cube compress_clut , output clut_pack.gmz
~~~
Once this file containing a _pack_ of _LUTs_ is generated, these 10 transformations are available via the **Colors / Apply From CLUT Set** filter, by specifying the `clut_pack.gmz` file as a parameter, as illustrated below.

===
[![clut set](https://gmic.eu/gmic325/thumbs/clut_set.png)](https://gmic.eu/gmic325/img/clut_set.jpg)
_Fig. 3.2.3. The ***Colors / Apply From CLUT Set*** filter, as seen in the G’MIC-Qt plug-in._
===

So here is a filter that avoids storing _sets_ of 3D color _LUTs_ of several megabytes to disk!

- To stay in the field of colorimetric transformations, here is the recent **Colors / Vibrance** filter, which makes the colors of your images ever more shimmering. There are other comparable filters available in _G'MIC_, but we thus have an alternative to the other similar algorithms already present. This filter comes from the user [_Age_](https://discuss.pixls.us/u/age/) who occasionally participates to discussions on our [forum](https://discuss.pixls.us/c/software/gmic/), hosted by our friends at [PIXLS.US](https://discuss.pixls.us/) (from which [Pat David](https://patdavid.net/), who also contributes to the [GIMP](https://www.gimp.org) project, is the instigator).

===
[![vibrance](https://gmic.eu/gmic325/thumbs/vibrance.png)](https://gmic.eu/gmic325/img/vibrance.jpg)
_Fig. 3.2.4. The ***Colors / Vibrance*** filter, as seen in the G’MIC-Qt plug-in._
===

## 3.3. The `color2name` and `name2color` commands

One last new feature concerning colors: the [`color2name`](https://gmic.eu/reference/color2name) and [`name2color`](https://gmic.eu/reference/name2color) command duo, which convert an _RGB_ color code to a color name, and vice versa. One example of use would be:

~~~
$ gmic 27,1,1,3 rand 0,255 split x foreach { color2name {^} resize 300,100 text_outline '${}',0.5~,0.5~,28 } frame 1,1,0 append_tiles 3
~~~

This pipeline builds a randomized array of named colors, in the shape of an image such as this one:

===
[![color2name](https://gmic.eu/gmic325/thumbs/color2name.png)](https://gmic.eu/gmic325/img/color2name.jpg)
_Fig. 3.3.1. An example use of the `color2name` command to name random colors._
===

The relation between the 881 color names recognized by these commands and their respective _RGB_ codes were gathered from [this Wikipedia page](https://en.wikipedia.org/wiki/Lists_of_colors). Below, the whole set of these 881 colors are represented in the _RGB_ cube:

===
[![color2name3d](https://gmic.eu/gmic325/thumbs/color2name3d.png)](https://gmic.eu/gmic325/img/color2name3d.jpg)
_Fig. 3.3.2. The whole set of named colors known to the `color2name` command._
===

# 4. 3D mesh and voxel structures

Did you know? Not only can _G'MIC_ manage regular images, but it is also able to manipulate [3D mesh objects](https://en.wikipedia.org/wiki/Polygon_mesh)? And even if 3D visualization and manipulation are not central objectives to the project, several interesting additions were implemented in this area.

## 4.1. Importing objects in the _Wavefront_ file format
First of all, _G’MIC_ can now import 3D objects stored in [_Wavefront_](https://en.wikipedia.org/wiki/Wavefront_.obj_file) `.obj` files, whereas previously only exporting was possible in this format (export which was also improved). Not all the characteristics of the `.obj` format are taken into account, but importing object geometry, colors and textures commonly works. Thus, the command:

~~~
$ gmic luigi3d.obj display3d
~~~

allows importing a 3D object to visualize it in a new window, as is depicted in the animation below.
A word of warning: the viewer integrated into _G'MIC_ doesn't benefit from _GPU_ graphic acceleration. Rendering may be quite slow if the mesh is made of many vertices (a clue for future improvement?).

===
[![luigi3d](https://gmic.eu/gmic325/img/v_luigi3d.gif)](https://gmic.eu/gmic325/img/v_luigi3d.gif)
_Fig. 4.1.1. Import and visualization of a textured 3D mesh in G'MIC._
===

Naturally, we have integrated this new 3D mesh import feature in the _G’MIC-Qt_ plug-in, with the new **Rendering / 3D Mesh** filter, which allows importing an `.obj` file and inserting a 3D render in an image, as shown in the video below:

===
[![mesh3d](https://gmic.eu/gmic325/thumbs/v_mesh3d.png)](https://gmic.eu/gmic325/img/v_mesh3d.mp4)
_Fig. 4.1.2 The ***Rendering / 3D Mesh*** filter in action, in the G’MIC-Qt plug-in._
===

It will be typically used to import a 3D object one wants to draw, orient it in space, and use it as a tracing « guide », either by redrawing it completely on a new layer placed above, or by using one of the many _G’MIC_ filters, to render it as a _cartoon_ drawing or a painting for example.

## 4.2. 3D meshes modification tools.

What else is there to do once the 3D mesh is loaded in memory/RAM? _G’MIC_ has the following features:

- Texture extraction, thanks to the new [`extract_textures3d`](https://gmic.eu/reference/extract_textures3d) command. The next 3 figures illustrate the case of a 3D mesh object depicting a cat, from which the texture is extracted and transformed with a stylization filter (modeled after the japanese print [The Great Wave off Kanagawa](https://en.wikipedia.org/wiki/The_Great_Wave_off_Kanagawa)), then reapplied to the cat.

===
[![cat obj](https://gmic.eu/gmic325/thumbs/cat_obj.png)](https://gmic.eu/gmic325/img/cat_obj.jpg)
_Fig. 4.2.1. View of a 3D mesh object depicting a cat, with its texture._
===

===
[![cat textures](https://gmic.eu/gmic325/thumbs/cat_textures.png)](https://gmic.eu/gmic325/img/cat_textures.jpg)
_Fig. 4.2.2. Texture extraction and stylization, via the `extract_textures3d` command._
===

===
[![v extract texture3d](https://gmic.eu/gmic325/thumbs/v_extract_texture3d.png)](https://gmic.eu/gmic325/img/v_extract_texture3d.mp4)
_Fig. 4.2.3. View of the original 3D mesh and its stylized version._
===

- A 3D object's faces can also be subdivided, thanks to the new [`subdivide3d`](https://gmic.eu/reference/subdivide3d) command.

===
[![subdivide3d](https://gmic.eu/gmic325/thumbs/subdivide3d.png)](https://gmic.eu/gmic325/img/subdivide3d.jpg)
_Fig. 4.2.4. Subdividing the faces of a 3D tore mesh with the `subdivide3d` command._
===

- A **textured** 3D object can be converted to solely **colored**, with the [`primitives3d`](https://gmic.eu/reference/primitives3d) command. The following command line applies this process on the _Luigi3d_ model previously introduced, to remove its texture and replace it with colored faces:

~~~
$ gmic luigi3d.obj primitives3d 2 output luigi3d_no_textures.obj
~~~

===
[![primitives3d](https://gmic.eu/gmic325/thumbs/primitives3d.png)](https://gmic.eu/gmic325/img/primitives3d.jpg)
_Fig. 4.2.5. Converting textured primitives to simply colored primitives, with the `primitives3d` command._
===

The average color of each face is computed from the colors of all of its vertices. For large faces, it might be very useful to subdivide the model beforehand, to get a high enough resolution of the colored texture in the final object (using the `subdivide3d` command).

- Finally, a 3D mesh object can also be converted to a **volumetric** image containing a **voxels** set, with the new [`voxelize3d`](https://gmic.eu/reference/voxelize3d) command. This command reshapes all the base primitives making up a 3D model (vertices, faces, edges, spheres) as discrete primitives traced in the volumetric image. For example, this command line:

~~~
$ gmic skull.obj voxelize3d 256,1,1 output skull_voxelized.tif display_voxels3d
~~~

will reshape the skull mesh illustrated below as a volumetric image made of colored voxels, that we can view with the new [`display_voxels3d`](https://gmic.eu/reference/display_voxels3d) command. Hence the very « [Minecraft-like](https://en.wikipedia.org/wiki/Minecraft) » render (voxelized below at different resolutions):

===
[![voxelize3d](https://gmic.eu/gmic325/thumbs/voxelize3d.png)](https://gmic.eu/gmic325/img/voxelize3d.jpg)
_Fig. 4.2.6. Converting a textured 3D mesh to a volumetric image made of colored voxels, with the `voxelize3d` command._
===

This feature will be useful, for example, to people studying the field of discrete geometry, who will be able to easily generate complex discrete 3D objects from meshes (more than often easier to create than their dicsrete counterparts!). The video below illustrates the render of a discrete 3D model thus created:

===
[![v display voxels3d](https://gmic.eu/gmic325/thumbs/v_nounours.png)](https://gmic.eu/gmic325/img/v_nounours.mp4)
_Fig. 4.2.7. Visualization video of a complex 3D mesh voxelized by the `voxelize3d` command._
===

## 4.3. 3D mesh generation tools

To conclude this section about 3D meshes in _G’MIC_, let's mention, in no particular order, the appearance of a few recent commands dédicated to 3D mesh procedural generation:

- The [`shape_menger`](https://gmic.eu/reference/shape_menger) and [`shape_mosely`](https://gmic.eu/reference/shape_mosely) commands produce volumetric representations (voxel images) of the following  mathematical fractals: the [Menger sponge](https://en.wikipedia.org/wiki/Menger_sponge) and the [Mosely snowflake](https://en.wikipedia.org/wiki/Mosely_snowflake).

===
[![menger sponge](https://gmic.eu/gmic325/thumbs/menger_sponge.png)](https://gmic.eu/gmic325/img/menger_sponge.jpg)
_Fig. 4.3.1. 3D renders of the Menger sponge and the Mosely snowflake, created with the `shape_menger` and `shape_mosely` commands._
===

===
[![v_menger_sponge](https://gmic.eu/gmic325/thumbs/v_menger_sponge.png)](https://gmic.eu/gmic325/img/v_menger_sponge.mp4)
_Fig. 4.3.2. Video of a Menger sponge, rendered by G'MIC._
===

- The [`chainring3d`](https://gmic.eu/reference/chainring3d) creates a 3D ring of color tores:

===
[![chainring3d](https://gmic.eu/gmic325/img/v_chainring3d.gif)](https://gmic.eu/gmic325/img/v_chainring3d.gif)
_Fig. 4.3.3. Rendering a ring of 3D color tores with the `chainring3d` command._
===

- The [`curve3d`](https://gmic.eu/reference/curve3d) generates the 3D mesh of the parametric curve `t → (x(t),y(t),z(t))`, with the optional `r(t)` radius thickness, which is also parametric.

===
[![curve3d](https://gmic.eu/gmic325/img/v_curve3d.gif)](https://gmic.eu/gmic325/img/v_curve3d_2.mp4)
_Fig. 4.3.4. Rendering a 3D parametric curve, created with the `curve3d` command._
===

- The [`sphere3d`]((https://gmic.eu/reference/sphere3d)) command is now able to generate 3D spherical meshes using three different methods: 1. isocahedron subdivision, 2. cube subdivision, and 3. the angular discretization in spherical coordinates. They are illustrated below, from left to right:

===
[![sphere3d](https://gmic.eu/gmic325/thumbs/sphere3d.png)](https://gmic.eu/gmic325/img/sphere3d.jpg)
_Fig. 4.3.5. Creation of 3D spherical meshes, with three different mesh algorithms, via the `sphere3d` command._
===

In practice, all these new 3D mesh generation commands can be inserted into more complex _G’MIC pipelines_, in order to proceduraly form sophisticated 3D objects. These meshes can then be exported as `.obj` files. It is illustrated here, with the creation of a recursive chain ring which was firstly generated by _G’MIC_ (using the `chainring3d` command as the base element as well), then imported into [_Blender_](https://www.blender.org) :

===
[![antoine3d](https://gmic.eu/gmic325/thumbs/antoine3d_blender.png)](https://gmic.eu/gmic325/img/antoine3d_blender.jpg)
_Fig. 4.3.6. Procedural generation of an object with G’MIC, then imported into Blender._
===

# 5. Other news

This last section gives some new informations related to the project, in no particular order.

## 5.1. Various improvements of the G'MIC-Qt plug-in

A lot of work has been done on the _G’MIC-Qt_ plug-in's code, even if not's not really visible at first. Let's mention in particular :

- Some code **important optimizations** which improve the plug-in's start up time: the plug-in window is displayed faster, the filter parser is more efficient, notably due to the use of a binary cache storing the analyzed filters' information after an update.
- Some **improvement** regarding plug-in **stability**. It more effectively handles threads launched by unfinished filters.
- A change in the interface's theme, which defaults to **dark mode**.
- The filter's elapsed/execution time is now displayed when the « _Apply_ » button is clicked.
- A new **external filter sources** management system: it becomes easy for a developper to share his personalized _G’MIC_ filters with a user, by giving him a file or an URL pointing to their implementation (in the same way a _[PPA](https://doc.ubuntu-fr.org/ppa)_ works for package managers in _Ubuntu_ ).

===
[![filter_sources](https://gmic.eu/gmic325/thumbs/filter_sources.png)](https://gmic.eu/gmic325/img/filter_sources.jpg) 
_Fig. 5.1.1. The new external filter sources management system in the G’MIC-Qt plug-in._
===

- The plug-in provides a way for filters to store persistent data in a memory cache across consecutive calls. This allows filters that need to load or generate large data, to only do it once, and reuse it in successive calls. This method is used by the **Rendering / 3D Mesh** filter to store a 3D object loaded from a file.
- Plugin-in code has been modified to alleviate the future transition to version 6 of the _Qt_ library.
- Thanks to [Nicholas Hayes](https://github.com/0xC0000054)' work, the _G’MIC-Qt_ plug-in is now available on [_Adobe's Marketplace_](https://exchange.adobe.com/apps/cc/109191/gmic). Thus, the plug-in setup is now simplified for [Photoshop](https://en.wikipedia.org/wiki/Adobe_Photoshop) users.

- Let's finally mention the plug-in's update for the latest version of [Digikam](https://www.digikam.org/) (v. 8.0.0), thanks to [Gilles Caulier](https://invent.kde.org/cgilles)'s work.
A [detailed/provided documentation](https://docs.digikam.org/en/image_editor/enhancement_tools.html#g-mic-qt-tool) was put online to _Digikam's_ website.

===
[![digikam](https://gmic.eu/gmic325/thumbs/digikam.png)](https://gmic.eu/gmic325/img/digikam.jpg)
_Fig. 5.1.2. The G’MIC-Qt plug-in is directly available inside Digikam, an open source photo management software._
===

## 5.2. Improvement of the `stdgmic` standard library

_G’MIC's_ standard library ([`stdgmic`](https://raw.githubusercontent.com/GreycLab/gmic/develop/src/gmic_stdlib.gmic)) contains the whole set of non native commands, directly written in the _G'MIC_ language, and by default provided with the framework. In practice, the vast majority of existing commands fall within this scheme. In addition to the new commands already described above, let's take note of the following inclusions and improvements in `stdgmic`:

- The `nn_lib` library, allowing simple **neural network learning**, acquired new modules (_Softmax Layer_, _Cross-Entropy Loss_, _Binary Cross-Entropy Loss_, _Conv3D_, _Maxpool3D_ and _PatchUp/PatchDown 2D/3D_). Its development is progressing gradually. It is already used by the **Repair / Denoise** filter, [already mentioned](https://gmic.eu/gmic300/#_2_2_image_enhancement) in our previous report. We have also implemented a few « toy » examples of statistical training using this library, such as the learning of a _(x,y) → (R,G,B)_ function depicting an image. Here, the idea is to train a neural network to reproduce a color image by providing, as learning data, the _(x,y)_ coordinates of the image's pixels (as input) and their corresponding _(R,G,B)_ colors (as output). The picture below shows the overall picture recosntructed by the network as learning iterations progress:

===
[![nnlib](https://gmic.eu/gmic325/thumbs/nnlib_xytorgb.png)](https://gmic.eu/gmic325/img/nnlib_xytorgb.jpg)
_Fig. 5.2.1. Neural network training of a (x,y) → (R,G,B) function depicting an image. Different iterations of the learning process are shown._
===

The complete learning sequence can be viewed in the video below :

===
[![v_nnlib](https://gmic.eu/gmic325/thumbs/v_nnlib_xytorgb.png)](https://gmic.eu/gmic325/img/v_nnlib_xytorgb.mp4)
_Fig. 5.2.2. Learning iterations sequence of the neural network for the training of a (x,y) → (R,G,B) function , representing an image._
===

We also have working examples of the `nn_lib` to automaticaly classify simple images (from the [_MNIST_](http://yann.lecun.com/exdb/mnist/) and [_Fashion MNIST_](https://github.com/zalandoresearch/fashion-mnist) data sets, among others). _G’MIC_ is then potentially able to detect the content of some images, like illustrated below with the classification of handwritten digits (we have in store a smiliar method for detecting human faces).

===
[![mnist](https://gmic.eu/gmic325/thumbs/mnist.png)](https://gmic.eu/gmic325/img/mnist.jpg) 
_Fig. 5.2.3. Automatic classification of pictures of handwritten digits (MNIST database) by a neural network, using G'MIC's `nn_lib` library._
===

An incomplete documentation about using this statistical learning library with the _G'MIC_ language is available on [our discussion forum](https://discuss.pixls.us/t/neural-networks-in-gmic-an-introduction-to-the-api-of-nn-lib/33536).

- Another feature of `stdgmic: the [match icp](https://gmic.eu/reference/match_icp) command implements the algorithm called « [Iterative Closest Point](https://en.wikipedia.org/wiki/Iterative_Closest_Point) » ( _ICP_ ), which matches two sets of _N_ dimensional vectors. This command can be used to determine the rigid geometric transformation (rotation + translation) between two _frames_ of an animation, even in presence of noise. The animation below shows this process, with two rigid transformations estimated by _ICP_, to respectively align the star and heart silhouettes.

===
[![lineaa](https://gmic.eu/gmic325/img/v_icp.gif)](https://gmic.eu/gmic325/img/v_icp.gif)
_Fig. 5.2.4. Aligning silhouettes with the « Iterative Closest Point » algorithm, using the `match_icp` command._
===

- Let's see now the new [`img2patches`](https://gmic.eu/reference/img2patches) and [`patches2img`](https://gmic.eu/reference/patches2img) commands:
they respectively allow decomposing and recomposing an image as a volumetric stack of thumbnails (« _patches_ »), possibly taking into account overlapping _patches_. For example, this command :

~~~
$ gmic butterfly.jpg img2patches 64
~~~
will transform the input image (below, left) into a volumetric stack of _patches_ (on the right ) :

===
[![img2patches0](https://gmic.eu/gmic325/thumbs/img2patches0.png)](https://gmic.eu/gmic325/img/img2patches0.jpg)
_Fig. 5.2.5. Transforming a color image into a volumetric stack of patches, with the `img2patches` command._
===

This set of _patches_ can then be processed, for example by sorting them in increasing variance order (therefore from the level of detail they possess), before rebuilding the image. As shown with the following pipeline :

~~~
$ gmic sample butterfly W,H:=w,h img2patches 64,0,3 split z sort_list +,iv append z patches2img '$W,$H'
~~~

This creates the image below, where _patches_ are more and more detailed as you look down into the image.

===
[![img2patches](https://gmic.eu/gmic325/thumbs/img2patches.png)](https://gmic.eu/gmic325/img/img2patches.jpg)
_Fig. 5.2.6. Sorting patches of an image by increasing detail level._
===

- The new [`line_aa`](https://gmic.eu/reference/line_aa) command implements [Xiaolin Wu](https://en.wikipedia.org/wiki/Xiaolin_Wu%27s_line_algorithm)'s algorithm for tracing [_anti-aliased_](https://en.wikipedia.org/wiki/Spatial_anti-aliasing) line segments, which means it tries to reduce the aliasing effect which usually appears when tracing primitives in discrete images.

===
[![lineaa](https://gmic.eu/gmic325/thumbs/lineaa.png)](https://gmic.eu/gmic325/img/lineaa.jpg)
_Fig. 5.2.7. Comparing traced line segments, between Brensenham's regular method and Xiaolin Wu's algorithm, implemented in the `line_aa` command._
===

- As a conclusion to this section about _G’MIC's_ standard library, let's talk about the arrival of the [ssim](https://gmic.eu/reference/ssim) (computation of the « _[Structural Similarity](https://en.wikipedia.org/wiki/Structural_Similarity)_ » between two images), [opening](https://gmic.eu/reference/opening), [opening_circ](https://gmic.eu/reference/opening_circ), [closing](https://gmic.eu/reference/closing), [closing_circ](https://gmic.eu/reference/closing_circ) (morphological opening and closing with a square of circular structural element), [betti](https://gmic.eu/reference/betti) (calculation of the [Betti_numbers](https://en.wikipedia.org/wiki/Betti_number), topological invariants of discretized shapes in 2D or 3D) and a new layer blending mode for the [blend](https://gmic.eu/reference/blend) command: `shapeprevalent`. As you can see, there is always new things to delve into ☺!

## 5.3. Various information related to the project

To conclude this long report, here is some general information on the _G’MIC_ project.

- Firstly, a reminder about the existence of [OpenFX](https://en.wikipedia.org/wiki/OpenFX_(API)) plug-ins embedding _G’MIC's_ functionalities, therefore allowing the application of most of our filters from video editing software implementing this _API_ (such as [Natron](https://en.wikipedia.org/wiki/Natron_(software)) or [Adobe After Effects](https://en.wikipedia.org/wiki/Adobe_After_Effects)).
See the [dedicated post](https://discuss.pixls.us/t/gmic-for-openfx-and-adobe-plugins) from the author of these plug-ins, [Tobias Fleischer](https://discuss.pixls.us/u/tobias_fleischer/).

===
[![openfx](https://gmic.eu/gmic325/thumbs/after_effect.png)](https://gmic.eu/gmic325/img/after_effect.jpg)
_Fig. 5.3.1. One of G’MIC's OpenFX plug-ins in action, from within Adobe After Effects._
===

===
[![openfx2](https://gmic.eu/gmic325/thumbs/natron.png)](https://gmic.eu/gmic325/img/natron.jpg)
_Fig. 5.3.2. One of G’MIC's OpenFX plug-ins in action, from within Natron._
===

- Our algorithm for [automatic illumination of solid color drawings](https://discuss.pixls.us/t/release-of-gmic-2-3-0/6800), already mentioned in a previous report (the **Illuminate 2D Shape** filter) was the subject of a research paper at the end of 2022, at the [_IEEE International Conference on Image Processing_](https://2022.ieeeicip.org/) in Bordeaux. This paper, titled « _[Automatic Illumination of Flat-Colored Drawings by 3D Augmentation of 2D Silhouettes](https://tschumperle.users.greyc.fr/publications/tschumperle_icip22.pdf)_ » explains in detail the algorithm used by this filter. This effect is appreciated by illustrators, who can use it to quickly give an embossed look to their solid color drawings, as shown in the following video:

===
[![illuminate_shape](https://gmic.eu/gmic325/thumbs/youtube_illuminate2d_shape.png)](https://www.youtube.com/watch?v=WQ2u639FgyQ)
_Fig. 5.3.3. Video tutorial on the use of the ***Illuminate 2D Shape*** filter to automaticaly illuminate a solid color drawing._
===

The more curious about the algorithm's technical details can view the following presentation, given to the _ICIP’2022_ conference:

===
[![illuminate_shape2](https://gmic.eu/gmic325/thumbs/youtube_illuminate2d_shape_icip.png)](https://www.youtube.com/watch?v=PmWlan_8Qdo)
_Fig. 5.3.4. Video explaining the algorithm behind the ***Illuminate 2D Shape*** filter._
===

- Let's remark that _G’MIC's_ scripting language is flexible enough to not only be used to conceive image manipulation filters, but also to create **interactive demo viewers**. At the _GREYC_ laboratory, it allowed us to develop two demo terminals around image processing. These viewers are exhibited on our stand during public events (for example at the [Fête de la Science](https://www.fetedelascience.fr/), or the [Festival de l’Excellence Normande](https://www.normandie-tourisme.fr/evenement/feno-festival-excellence-normande/)).

The first of these demo viewers can be observed by clicking on the picture below (presented by our colleague [Loïc Simon](https://simonl02.users.greyc.fr/)). It illustrates the matter of « _style transfer_ » between two images. It runs on a touch table.

===
[![demo_table_tactile](https://gmic.eu/gmic325/thumbs/demo_table_tactile.png)](https://www.vip-studio360.fr/galerie360/visites/vv-ensicaen/vv-ensicaen-2022-c.html?s=pano41&h=0&v=0.0000&f=90.0000&skipintro&norotation)
_Fig. 5.3.5. Preview of G'MIC's style transfer demo viewer (click on the image to view the 360° demo)._
===

The second one allows to play with an interactive distorting mirror, as shown in the video below:

===
[![greyc_warp](https://gmic.eu/gmic325/thumbs/v_greyc_warp.png)](https://gmic.eu/gmic325/img/v_greyc_warp.mp4)
_Fig. 5.3.6. Interactive image distortion demo viewer, implemented with the G’MIC language._
===

- As a personal project, I've started to write a simple [_raytracer_](https://en.wikipedia.org/wiki/Ray_tracing) with the _G’MIC_ language, to test it's capabilities. The goal isn't necessarily to go very far (because time is lacking, but it is very interesting in practice!), but it is a good way to uncover interesting optimizations which could be made to the _G’MIC_ interpreter in the future. A simple object animation, generated by this _raytracer_ under development, is shown below:

===
[![raytracer](https://gmic.eu/gmic325/thumbs/v_raytracer.png)](https://gmic.eu/gmic325/img/v_raytracer.mp4)
_Fig. 5.3.7. Example of raytracing rendering, implemented in G'MIC language (under development)._
===

- For those who want to know more about _G’MIC's_ language operation, we suggest reading the [amazing tutorial pages](https://gmic.eu/tutorial/) written by [Garry Osgood](https://discuss.pixls.us/u/grosgood), who contributes to the _G’MIC_ project documentation since several years. Notably, he wrote [a series of articles on the creation of arabesques](https://gmic.eu/tutorial/wheelies.html) that we can only recommend!

===
[![arabesque](https://gmic.eu/gmic325/thumbs/v_arabesque.png)](https://gmic.eu/gmic325/img/v_arabesque.mp4) 
_Fig. 5.3.8. Example of silhouette tracing using the arabesque method described in Garry Osgood tutorial._
===

- Note that with _G'MIC's_ language, it is also possible to create funny [one-liners](https://fr.wiktionary.org/wiki/one-liner), which are pipelines fitting on a single line and generating peculiar images or animations. The two following pipelines are good examples:

**One-liner N°1**: Generating a fixed color image (a flash of lights).

~~~
$ gmic 500,500 repeat 10 { +noise_poissondisk[0] '{3+$>}' } rm[0] a z f '!z?(R=cut(norm(x-w/2,y-h/2)/20,0,d-1);i(x,y,R)):0' slices 0 to_rgb f 'max(I)?u([255,255,255]):I' blur_radial 0.6% equalize n 0,255
~~~

===
[![lightspeed](https://gmic.eu/gmic325/thumbs/lightspeed.png)](https://gmic.eu/gmic325/img/lightspeed.jpg)
_Fig.5.3.9. Results of the first one-liner._
===

**One-liner N°2 :** Creating a « dinosaur skin » color animation.

~~~
$ gmic 300,300x5 foreach { noise_poissondisk 40 +distance 1 label_fg.. 0 mul. -1 watershed.. . rm. g xy,1 a c norm neq 0 distance 1 apply_gamma 1.5 n 0,255 } morph 20,0.1 map copper +rv[^0] animate 40
~~~

===
[![reptile_skin](https://gmic.eu/gmic325/img/v_reptile_skin.gif)](https://gmic.eu/gmic325/img/v_reptile_skin.gif)
_Fig.5.3.10. Results of the second one-liner._
===

- The two pictures below result from experiments with the _G’MIC_ language made by [_Reptorian_](https://discuss.pixls.us/u/reptorian), a long time contributor, who very much explores the language's generative art capabilities.

===
[![generative_art2](https://gmic.eu/gmic325/thumbs/ga_reptorian_da2.png)](https://gmic.eu/gmic325/img/ga_reptorian_da2.jpg)
_Fig.5.3.11. Variation on the technique of « _[Diffusion-limited aggregation](https://en.wikipedia.org/wiki/Diffusion-limited_aggregation)_ », guided by image geometry (by Reptorian)._
===

===
[![generative_art3](https://gmic.eu/gmic325/thumbs/ga_reptorian.png)](https://gmic.eu/gmic325/img/ga_reptorian.jpg)
_Fig.5.3.12. Generating a fractal pattern (by Reptorian)._
===

Many other examples are available in [his forum thread](https://discuss.pixls.us/t/gmic-fun-with-reptorian/).

- Concerning the « communication » aspect of the project, a [_Twitter account_](https://twitter.com/gmic_eu) was created several years ago, where we regularly post news of the project's growth, new features implementation, new version releases, etc. From now on, we also have [a Mastodon_account](https://piaille.fr/@gmic), where we post news of the project. Do not hesitate to subscribe!

===
[![mastodon](https://gmic.eu/gmic325/thumbs/mastodon.png)](https://piaille.fr/@gmic)
_Fig. 5.3.13. Preview of G’MIC's Mastodon account._
===

- On social networks, we sometimes come accross unexpected _posts_ of people showing their use of _G’MIC_. For example, this series of recent _posts_ involves the processing of astronomical images with _G’MIC_ filters, to remove denoise or artistically enhance pictures.

===
[![astro](https://gmic.eu/gmic325/thumbs/astro.png)](https://gmic.eu/gmic325/img/astro.jpg)
_Fig. 5.3.14. Using G'MIC to process astronomical images._
===

You can find these _posts_ [here](https://twitter.com/navaneeth_ank/status/1620110820272410624), [there](https://twitter.com/SpaceGeck/status/1594213385377574913), [there](https://twitter.com/stim3on/status/1594292010000814080), and [also there](https://twitter.com/navaneeth_ank/status/1659381911255654400). This user feedback is obviously rewarding for us. If you are a (happy ☺) _G’MIC_ user yourself, do no hesitate to share your creations or your feedback. It's always a pleasure!

- Finally, let's mention the fact that _G’MIC_ was the subject of articles written by [Karsten Gunther](https://linuxformat.com/archives?author_find=217) in issues number _301_ and _302_ of the [LinuxFormat](https://www.linuxformat.com/) magazine (published in may and june 2023). They present the different photo editing capabilities provided by the _G’MIC-Qt_ plugin in a very educational way (just like we try to do in our reports on [_Linuxfr_](https://linuxfr.org/tags/gmic/public)!).

===
[![linux_format](https://gmic.eu/gmic325/thumbs/linux_format.png)](https://gmic.eu/gmic325/img/linux_format.jpg)
_Fig. 5.3.15. The « Linux Format » magazine offer a series of articles on using G’MIC-Qt, in its may and june 2023 issues._
===

Here, this concludes our roundup of the _G’MIC_ project's latest developments and information.

# 6. Conclusions & outlook

After **15 years** of developing _G’MIC_ and **24 years** of developing [_CImg_](http://cimg.eu), the _C++_ library which serves as its foundation, we now have a free and open source digital image manipulation framework, which is mature and has proven its usefulness in solving various image processing problems. Downloads keep on rising since writing the first lines of code (in 2008), proving that it is a dynamic project which attracts a wide range of users.

Will this dynamism continue? Of course we still have ideas to improve this framework. But at the same time, as professionnal duties increase, the time available for its development decreases. So going forward, the strategy will be:

- To properly choose which improvement paths to work on.
- To attempt to find external development time (either voluntary or funded).

On the short term, we are looking for contributors:

- To push forward the development of _G’MIC's_ [Python](https://www.python.org/) [binding](https://pypi.org/project/gmic/). It needs to be updated and devoted enough time to thoroughly test it, to make _G’MIC_ usable directly from a _Python_ program, without _bugs_. Existing _binding_ is functional and is already a good working basis.
- To succeed in _packaging G’MIC_ for [macOS](https://en.wikipedia.org/wiki/MacOS). We indeed receive a lot of requests from _Mac_ users who don't know how to build and install the _G’MIC-Qt_ plug-in for _GIMP_.
  
If you think you can contribute on one of these two subjects, [do not hesitate to contact us!](https://discuss.pixls.us/c/software/gmic)

Finally, the revolution induced by the use of neural network in the field of digital image processing is fundamental. On this point, _G’MIC_ has some catching up to do. Until now, we mainly have focused on « standard » algorithmic image processing. Our `nn_lib` library should be developped faster to be able to deploy larger neural networks (a few dozens/hundreds of millions of parameters would already be satisfying!), to allow image processing or synthesis using more advanced statistical learning.

As you can see, we are not lacking ideas!

To conclude, let's not forget that _G’MIC's_ development couldn't have happened witout the encouragement and support of [_GREYC_](https://www.greyc.fr/), our laboratory, and its guardianships: the [CNRS INS2I institute](https://www.ins2i.cnrs.fr/fr), the [University of Caen Normandie](https://www.unicaen.fr/), and the [_ENSICAEN_](https://www.ensicaen.fr/). Huge thanks to them for the help on multiple levels during these last fifteen years of development. For some time, in the domain of scientific research, some interesting initiatives have been taking place in France to promote open and reproducible science ([national plan for open science](https://www.ouvrirlascience.fr/deuxieme-plan-national-pour-la-science-ouverte-pnso/), [CNRS open science plan](https://www.science-ouverte.cnrs.fr/), …), and open source software ([CNRS Open Innovation](https://www.cnrsinnovation.com/open/) promoting program). These are encouraging signs for researchers who often invest a lot of time creating free digital commons (software, data sets, etc.), and sometimes have trouble promoting their work as significant scientific contributions.

We hope that you have enjoyed this report. See you in a few ~~months~~ semesters, we hope, with once again a lot of new features to share with you all!
