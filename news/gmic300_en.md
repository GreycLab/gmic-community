# G'MIC 3.0: A Third Dose to Process Your Images!

_by [David Tschumperlé](https://tschumperle.users.greyc.fr/)_

A new major version (numbered **3.0.0**) of [_G'MIC_](https://gmic.eu) (_GREYC's Magic for Image Computing_), an open source [framework](https://en.wikipedia.org/wiki/Software_framework) for [image processing](https://en.wikipedia.org/wiki/Digital_image_processing), was released on December 9th 2021. This project, distributed under the [_CeCILL_](https://en.wikipedia.org/wiki/CeCILL) free software license, is mainly developed by the [_IMAGE_](https://www.greyc.fr/en/equipes/image-2/) team of [_GREYC_](https://www.greyc.fr/en/home/), a French research laboratory in Information and Communication Sciences and Technologies (Mixed Research Lab [_CNRS_](https://www.cnrs.fr/en) / [_ENSICAEN_](https://www.ensicaen.fr/en/) / [University of Caen](http://welcome.unicaen.fr/)).

===
[![gmic_teaser](https://gmic.eu/gmic300/fullsize/gmic_teaser.gif)](https://gmic.eu/gmic300/fullsize/gmic_teaser.gif)
===

The [last report](https://pixls.us/blog/2019/09/g-mic-2-7-process-your-images-with-style/) on this software was published over two years ago, in August 2019. Since then many new features have been released. In this article, we detail some of the most significant ones.

It's time to make a hot drink, get comfortable on the couch and let us tell you about two years of development of a dynamic, free project!

_Note: click on the images to get higher resolution versions._

# 1. _G'MIC_ In Just Over 3.0.0 Words

[_G'MIC_](https://gmic.eu) is an open-source framework for [digital image](https://en.wikipedia.org/wiki/Digital_image) manipulation and processing.

It offers various user interfaces for the algorithmic manipulation (automated or semi-automated) of images and generic signals, ranging from simple 1D signals to 3D volumetric image sequences with any number of channels (which includes classical color images). The core of this project is based on the definition of a specialized scripting language (the [_"G'MIC language"_]((https://gmic.eu/reference/overall_context.html)) and on a free implementation of its associated interpreter. This language was specifically developed to ease the prototyping and implementation of new image processing algorithms and operators. The users of the framework can thus apply operations among the hundreds already predefined, but also have the possibility if writing their own complex processing pipelines and make them accessible in the various user interfaces of the project. _G'MIC_ is therefore, in essence, an open, extensible and constantly evolving framework.

===
[![G’MIC logo](https://gmic.eu/gmic300/thumb/logo_gmic.png)](https://gmic.eu/gmic300/fullsize/logo_gmic.jpg)
_Fig. 1.1 : Logo of the G'MIC project, a free image processing software, and its mascot "Gmicky" (created by [David Revoy](https://www.davidrevoy.com/))._
===

The _G'MIC_ project has been developed since 2008, mainly by two members of the [_IMAGE_](https://www.greyc.fr/en/equipes/image-2/) team of the [_GREYC_](https://www.greyc.fr/en/home/) laboratory: [David Tschumperlé](https://tschumperle.users.greyc.fr/) ([_CNRS_](https://www.cnrs.fr/en) research fellow, team leader) and [Sébastien Fourey](https://foureys.users.greyc.fr/Fr/index.php) ([_ENSICAEN_](https://www.ensicaen.fr/en/) lecturer). The _IMAGE_ team, one of the six teams of the _GREYC_, is composed of about fifty members (researchers, teacher-researchers, doctoral and post-doctoral students, engineers), all specialized in the fields of algorithmics and mathematics of image processing.

The most visible _G'MIC_ user interfaces are: the [`gmic`](https://gmic.eu/reference/) command, which can be used on the command line (an essential companion to [_ImageMagick_](https://www.imagemagick.org/) or [_GraphicsMagick_](http://www.graphicsmagick.org) for those who process their images via the terminal), the [_G’MIC Online_](https://gmicol.greyc.fr/) Web service, and above all, the [_G’MIC-Qt_](https://github.com/c-koi/gmic-qt) plugin, which is available for several popular digital image editing software (free or proprietary) such as [_GIMP_](https://www.gimp.org), [_Krita_](https://www.krita.org), [_Paint.net_](https://www.getpaint.net), and more recently, [_Adobe Photoshop_](https://en.wikipedia.org/wiki/Adobe_Photoshop) or [_Affinity Photo_](https://en.wikipedia.org/wiki/Affinity_Photo). This plugin allows you to enrich these programs with more than 570 different filters and effects to apply to images.

===
[![Greffon G’MIC-Qt](https://gmic.eu/gmic300/thumb/gmic300.png)](https://gmic.eu/gmic300/fullsize/gmic300.jpg)
_Fig. 1.2: Overview of the G'MIC-Qt plugin, version 3.0.0, here launched from GIMP 2.10._
===

Thanks to its integrated scripting language, facilitating the prototyping and implementation of image processing algorithms and operators, new filters are regularly created and added to _G'MIC_. A large part of this article will be dedicated to the description of the new filters and effects developed in the last two years.

# 2. New Features of the G'MIC-Qt Plug-In

_G'MIC-Qt_ is the most popular and most used interface of the _G'MIC project_, so let's start by describing the new features concerning it. An exhaustive list of the new filters would be impossible here, since in fact more than fifty new entries have been added in two years! We have tried to follow the adage _"A picture is worth a thousand words"_, by sprinkling this article with numerous figures illustrating the new features.

## 2.1. Artistic Effects

- The new **Artistic / Paint With Brush** filter is in the great tradition of effects that seek to transform a photograph into a drawing or painting. Its originality lies in the fact that it will repaint the entire image given as input on a virtual white canvas, applying successive brushstrokes at different scales: first with coarse brushes, then with increasingly fine brushes to recreate the smallest details of the image.

===
[![gmic_paint_with_brush](https://gmic.eu/gmic300/thumb/gmic_paint_with_brush.png)](https://gmic.eu/gmic300/fullsize/gmic_paint_with_brush.jpg)
_Fig.2.1.1. The " Artistic / Paint With Brush " filter in action._
===

Here, everything is adjustable: the number of brush strokes at each iteration, the brush dynamics (size, opacity, color, orientation...), the geometric precision of the strokes, etc. This makes it a very versatile filter, allowing it to simulate various painting styles. This can be seen in the animation below, which shows the results obtained with several provided presets.

===
[![gmic_paint_with_brush](https://gmic.eu/gmic300/fullsize/gmic_paint_with_brush_anim.gif)](https://gmic.eu/gmic300/fullsize/gmic_paint_with_brush_anim.gif)
_Fig.2.1.2. The different presets proposed allow to simulate several painting styles._
===

- In the same vein, the **Artistic / Doodle** filter redraws an image in the form of "doodles", i.e. a set of continuous black lines on a white background, located mainly on the outlines of objects present in the images, as illustrated by the result below.

===
[![gmic_doodle](https://gmic.eu/gmic300/fullsize/gmic_doodle.gif)](https://gmic.eu/gmic300/fullsize/gmic_doodle.gif)
_Fig.2.1.3. Result of the "Artistic / Doodle" filter._
===

- Still in the spirit of converting an image into an illustration, the **Artistic / Comic Book** filter has been recently added to the plugin and allows you to give a cartoon look to your images. This is a "community" filter, since it was created by [Claude Lion](https://github.com/cl4cnam), a new contributor to the project, and then slightly modified by myself.

===
[![gmic_comic_book](https://gmic.eu/gmic300/thumb/gmic_comic_book.png)](https://gmic.eu/gmic300/fullsize/gmic_comic_book.jpg)
_Fig.2.1.4. The "Artistic / Comic Book" filter in action._
===

- Want to scare your kids just before bedtime, to make sure they have a good night's sleep? The new **Artistic / Ghost** filter is for you! This algorithm agglomerates semi-transparent white segments on the outlines of objects, which often results in quite nightmarish images (especially when applied on portraits).

===
[![gmic_ghost](https://gmic.eu/gmic300/thumb/gmic_ghost.png)](https://gmic.eu/gmic300/fullsize/gmic_ghost.jpg)
_Fig.2.1.5. The "Artistic/Ghost" filter in action. Keep the children away!_
===

It is then easy, by mixing the result of this effect with the original image (through well chosen layer merging modes) to generate animations, which will transform any of your images into a horror show! (here we used it in conjunction with the _G'MIC_ [`morph`](https://gmic.eu/reference/morph) command to render the animation below).

===
[![gmic_ghost](https://gmic.eu/gmic300/fullsize/gmic_ghost_anim2.gif)](https://gmic.eu/gmic300/fullsize/gmic_ghost_anim.gif)
_Fig.2.1.6. Animated variation around the " Artistic / Ghost " filter._
===

- Finally, let's mention two small improvements to existing artistic filters. First of all, the **Frames / Droste** filter has been equipped with interactive points that can be manipulated in the preview window, making it easier to adjust the area where the input image is repeated. These are the colored points visible at the four corners of the mirror, on the example below.

===
[![gmic_droste](https://gmic.eu/gmic300/thumb/gmic_droste.png)](https://gmic.eu/gmic300/fullsize/gmic_droste.jpg)
_Fig.2.1.7. Addition of user-manipulable points for the "Frames / Droste" filter setting._
===

Next, the **Artistic / Stylize** filter gets six new preset styles, developed by [Christine Garner](https://thimblefolio.com/), an artist who had used the filter extensively to give her images a textured look before offering her contribution. These new styles allow, for example, the production of images with pencil, chalk, pastel or charcoal textures.

===
[![gmic_stylize](https://gmic.eu/gmic300/thumb/gmic_stylize.png)](https://gmic.eu/gmic300/fullsize/gmic_stylize.png)
_Fig.2.1.8. One of the new predefined styles available in the "Artistic / Stylize" filter._
===

## 2.2. Image Enhancement

- The plugin has yet another new algorithm to help with image denoising, a classic yet very challenging problem that has occupied image processing researchers for several generations. The new **Repair / Denoise** filter tries to solve this task using an algorithm based on [convolutional neural networks](https://en.wikipedia.org/wiki/Convolutional_neural_network).

===
[![gmic_denoise](https://gmic.eu/gmic300/thumb/gmic_denoise.png)](https://gmic.eu/gmic300/fullsize/gmic_denoise.jpg)
_Fig.2.2.1. The "Repair / Denoise" filter in action._
===

At first sight, this information may seem trivial, but it actually represents a milestone in the history of _G'MIC_ (as well as many weeks of development!). Indeed, to implement this filter, we had to write a complete [machine learning](https://en.wikipedia.org/wiki/Machine_learning) library from scratch, named `nn_lib` (for _"**N**eural **N**etwork **Lib**rary"_). This library now allows the construction, learning, and evaluation of [artificial neural networks](https://en.wikipedia.org/wiki/Artificial_neural_network) (this type of method being generally referred to as ["Artificial Intelligence"](https://en.wikipedia.org/wiki/Artificial_intelligence)). The **Repair / Denoise** denoising filter is actually the first _G'MIC_ filter based on this new machine learning library!

===
[![gmic_denoise_balloons](https://gmic.eu/gmic300/thumb/gmic_denoise_balloons.png)](https://gmic.eu/gmic300/fullsize/gmic_denoise_balloons.jpg)
[![gmic_denoise_parrot](https://gmic.eu/gmic300/thumb/gmic_denoise_parrot.png)](https://gmic.eu/gmic300/fullsize/gmic_denoise_parrot.jpg)
_Fig.2.2.2. Two examples of image denoising, obtained with the "Repair / Denoise" filter._
===

With the development of `nn_lib`, we hope to offer more and more neural network based filters for image editing and generation in _G'MIC_ in the future. Great things to come!

- Another more specialized image enhancement filter has been integrated into the _G'MIC-Qt_ plugin. It is the **Repair / Unpurple** filter whose role is to remove the [purple fringing]((https://en.wikipedia.org/wiki/Purple_fringing) that can appear in photographs. The algorithm used here is a direct port in _G'MIC_ language of the [Unpurple](https://github.com/mjambon/purple-fringe) algorithm by [Martin Jambon](https://github.com/mjambon), port made by [Stanislav Paskalev](https://github.com/spaskalev). We can see the effect of this filter below, on a portion of an image with annoying purple fringes.

===
[![gmic_unpurple](https://gmic.eu/gmic300/thumb/Purple_fringing.png)](https://gmic.eu/gmic300/fullsize/Purple_fringing.jpg)
_Fig.2.2.3. Portion of color photograph with purple fringing._
===

===
[![gmic_unpurple](https://gmic.eu/gmic300/thumb/gmic_unpurple.png)](https://gmic.eu/gmic300/fullsize/gmic_unpurple.jpg)
_Fig.2.2.4. The "Repair / Unpurple" filter in action._
===

===
[![gmic_unpurple](https://gmic.eu/gmic300/thumb/Purple_fringing2.png)](https://gmic.eu/gmic300/fullsize/Purple_fringing2.jpg)
_Fig.2.2.5. Result of the filter: the purple fringe has disappeared._
===

- Suddenly feel like enhancing the details in your images? The new **Details / Sharpen [Multiscale]** filter may be of interest to you. It enters the armada of existing sharpening algorithms in _G'MIC_. It is based on a multi-scale enhancement algorithm to bring out details of different sizes in images.

===
[![gmic_sharpen_multiscale](https://gmic.eu/gmic300/thumb/gmic_sharpen_multiscale.png)](https://gmic.eu/gmic300/fullsize/gmic_sharpen_multiscape.jpg)
_Fig.2.2.6. The " Details / Sharpen [Multiscale] " filter in action._
===

===
[![gmic_sharpen_multiscale_anim](https://gmic.eu/gmic300/fullsize/gmic_sharpen.gif)](https://gmic.eu/gmic300/fullsize/gmic_sharpen.gif)
_Fig.2.2.7. Result of the application of the filter on a color photograph._
===

## 2.3. Color Retouching

For the color retouching of images, two new particularly interesting filters appear in _G'MIC-Qt_:

First, the **Colors / Tune HSV Colors** filter, which allows the user to define - in a very finely tuned way - a transformation function operating in the [HSV (Hue-Saturation-Value)](https://en.wikipedia.org/wiki/HSL_and_HSV) color space. This filter works in the following way:

- First, the filter will determine the existing colors in the input image closest to the following pure colors: red (denoted _R_), yellow (_Y_), green (_G_), cyan (_C_), blue (_B_) and magenta (_M_). The darkest (_D_), lightest (_L_), and average colors (_A_) are added to this list. It's possible that the input image does not contain any of these colors at all, and in this case the closest extracted color may be perceptually quite far from the ideal pure color. This is the case for example with the image of the butterfly shown below: this image contains no pixels in blue tones.

===
[![gmic_tune_hsv1](https://gmic.eu/gmic300/thumb/gmic_tune_hsv1.png)](https://gmic.eu/gmic300/fullsize/gmic_tune_hsv1.jpg)
_Fig.2.3.1. The " Colors / Tune HSV Colors " filter first extracts basic colors from the image._
===

- These nine colors extracted from the image will then be used as a basis for the definition of a custom color transformation. We can indeed modify each of these colors independently in the _HSV_ space, by making the color more or less bright, more or less saturated, or by changing its hue. This is what we do in the example below where we modify the reddest and magenta colors to make them green and thus change the color of the flower on which the butterfly is placed (whose hue has also been slightly modified).

===
[![gmic_tune_hsv0](https://gmic.eu/gmic300/thumb/gmic_tune_hsv0.png)](https://gmic.eu/gmic300/fullsize/gmic_tune_hsv0.jpg)
_Fig.2.3.2. The user can act on each of the 9 "key colors" individually to define a customized color transformation._
===

From a technical point of view, this redefinition of the "key colors" leads initially to the construction of a dense interpolated [_CLUT_ (_Color LUT_)](https://www.bromptontech.com/what-is-a-3d-lut/) in 3D, which is then used to modify the input image according to the wishes of the user, as illustrated below in our example with the butterfly:

===
[![fig_hsv](https://gmic.eu/gmic300/thumb/fig_hsv.png)](https://gmic.eu/gmic300/fullsize/fig_hsv.jpg)
_Fig.2.3.3. Internally, G'MIC generates a 3D CLUT modeling the desired colorimetric transformation._
===

The use cases of this filter are quite large. Whether it is for a local color retouch (transformation of one color into another), or a more global colorimetric retouch, this filter will easily find its place in the toolbox of the color tweaker. In the figure below, we used this filter to define a twilight color atmosphere.

===
[![gmic_tune_hsv2](https://gmic.eu/gmic300/thumb/gmic_tune_hsv2.png)](https://gmic.eu/gmic300/fullsize/gmic_tune_hsv2.jpg)
_Fig.2.3.4. Global color transformation applied to an image of [Pepper & Carrot](https://www.peppercarrot.com/) by artist [David Revoy](https://www.davidrevoy.com/)._
===

A demonstration video of this filter can be seen on the Youtube channel of Pierre _"El Lobo"_, who regularly posts tutorials in French on how to use _GIMP_. Click on the image below to access it. More details on how to use this filter can also be found on the [_G'MIC_ forum](https://discuss.pixls.us/t/filter-colors-tune-hsv-colors/21920).
===
[![video_tune_hsv](https://gmic.eu/gmic300/thumb/small_video_tune_hsv.png)](https://www.youtube.com/watch?v=AvfusCL0YpA)
===

The second notable colorimetric retouching filter is called **Colors / Transfer Colors [PCA]**. It makes it possible to transfer the colors of a reference image to a target image which one wishes to modify. Technically, this transfer is made by imposing the covariance matrix of the image to be modified to match that of the reference image.

===
[![gmic_transfer_pca](https://gmic.eu/gmic300/thumb/gmic_transfer_pca.png)](https://gmic.eu/gmic300/fullsize/gmic_transfer_pca.jpg)
_Fig.2.3.5. The "Colors / Transfer Colors [PCA]" filter in action._
===
===
[![gmic_transfer_pca_anim](https://gmic.eu/gmic300/fullsize/gmic_transfer_pca.gif)](https://gmic.eu/gmic300/fullsize/gmic_transfer_pca.gif)
_Fig.2.3.6. Result of the color transfer. The colors of the reference image (snowmen) were transferred to the bird image._
===

Note that the underlying color transfer algorithm is not only used for this filter, but has also been integrated as a sub-part of more complex processes (e.g. the **Artistic / Stylize** filter mentioned earlier).

## 2.4. Deformations and Degradations

Lovers of image distortion and [Glitch art](https://en.wikipedia.org/wiki/Glitch_art) may also be interested in this new version _3.0_ of _G'MIC_.

- Firstly, with the new **Deformations / Breaks** filter, which randomly introduces triangular discontinuities into the images. This filter was originally requested by the artist [David Revoy](https://www.davidrevoy.com/) to generate a deformation similar to that of an older filter, **Deformations / Crease**, but with sharper cuts. Two new deformation modes were implemented for this effect (_Flat_ and _Relief_ modes) with the following result:

===
[![gmic_breaks](https://gmic.eu/gmic300/fullsize/gmic_breaks.gif)](https://gmic.eu/gmic300/fullsize/gmic_breaks.gif)
_Fig.2.4.1. Application of the two different modes of the " Deformations / Breaks " filter on a color image._
===

Below, David Revoy demonstrates an application of this image break filter in the context of illustration, for a rendering of magical lightning with a most beautiful effect!

===
[![gmic_breaks_revoy](https://gmic.eu/gmic300/thumb/gmic_breaks.png)](https://gmic.eu/gmic300/fullsize/gmic_breaks.png)
_Fig.2.4.2. Use of the " Deformations / Breaks " filter to distort the shape of magic flashes._
===

A more detailed video of David Revoy using this type of filter can be seen at the following link:
===
[![video_crease](https://gmic.eu/gmic300/thumb/small_video_crease.png)](https://www.youtube.com/watch?v=vopP_8kJMj8)
===

- Another very glitchy effect: the **Degradations / Rebuild From Blocks** filter tries to rebuild an image from all its blocks. It does not position them all in their original place, but does allow itself to reuse the same block if necessary. As you can imagine, the result looks vaguely like the initial image but with a very pronounced block effect.

===
[![gmic_rebuild_from_blocs](https://gmic.eu/gmic300/thumb/gmic_rebuild_from_blocs.png)](https://gmic.eu/gmic300/fullsize/gmic_rebuild_from_blocs.jpg)
_Fig.2.4.3. The filter " Degradations / Rebuild From Blocks " will change the positions of the blocks in the image._
===

It is funny to notice that in the example above, the blocks corresponding to the eyes have simply been reversed in the two images!

- Finally, the **Degradations / Blur [Multidirectional]** filter applies, as its name suggests, a multi-directional blur effect to the image. It is possible to adjust the number of simultaneous blur directions, as well as to enhance local contrast in the resulting image.

===
[![gmic_blur_multi](https://gmic.eu/gmic300/thumb/gmic_blur_multi.png)](https://gmic.eu/gmic300/fullsize/gmic_blur_multi.jpg)
_Fig.2.4.4. The " Degradations / Blur [Multidirectional] " filter in action._
===

===
[![gmic_blur_multi2](https://gmic.eu/gmic300/thumb/gmic_blur_multi2.png)](https://gmic.eu/gmic300/fullsize/gmic_blur_multi2.png)
_Fig.2.4.5. Results obtained with different filter settings._
===

## 2.5. Rendering of Shapes and Patterns

Now let's enter the wonderful world of rendering filters. This is a unique category where you can find all sorts of oddities, filters that seem to have no use at all, until one day they become perfectly indispensable… or not! The following filters, which appeared in _G'MIC_ _3.0_, are no exception to this rule. They may be of little use to you, but they are still nice!

- Let's start with the simplest of them, the **Silhouettes / Others / Dragon Curve** filter, whose purpose is to draw the [Dragon Curve](https://en.wikipedia.org/wiki/Dragon_curve), a fractal curve composed of a single continuous line, built iteratively.

===
[![gmic_dragoncurve](https://gmic.eu/gmic300/fullsize/gmic_dragon.gif)](https://gmic.eu/gmic300/fullsize/gmic_dragon.gif)
_Fig.2.5.1. Different iterations of the construction of the dragon curve._
===

- Let's quickly move on to the **Rendering / Hypotrochoid** filter which, again, aims to draw a particular sine curve, namely a [Hypotrochoid](https://en.wikipedia.org/wiki/Hypotrochoid).

===
[![gmic_hypotrochoid](https://gmic.eu/gmic300/thumb/gmic_hypotrochoid.png)](https://gmic.eu/gmic300/fullsize/gmic_hypotrochoid.jpg)
_Fig.2.5.2. The " Rendering / Hypochotroid " filter in action._
===

- Still in the world of curve drawing, let's take a closer look at the new **Rendering / Sine Curve** filter, which defines a family of 2D or 3D [parametric curves](https://en.wikipedia.org/wiki/Parametric_equation), with a large number of user-adjustable parameters (nearly 50!).

===
[![gmic_sine_curve](https://gmic.eu/gmic300/thumb/gmic_sine_curve.png)](https://gmic.eu/gmic300/fullsize/gmic_sine_curve.jpg)
_Fig.2.5.3. The " Rendering / Sine Curve " filter in action._
===

There are a lot of parameters, so this filter offers a set of presets to play with all possible curve variations. The figure below illustrates some of the predefined shapes offered by the algorithm.

===
[![gmic_sine_curve_presets](https://gmic.eu/gmic300/thumb/gmic_sine_curve_presets.png)](https://gmic.eu/gmic300/fullsize/gmic_sine_curve_presets.jpg)
_Fig.2.5.4. Some parameter presets provided by the " Rendering / Sine Curve " filter._
===

As you can see, this filter allows you to draw a wide variety of parameterized sine curves. It can be used to generate shimmering backgrounds. Pierre _"El Lobo"_ has also made a short video tutorial on this filter (in French), which can be seen on his _Youtube_ channel (follow the link below)
===
[![video_sine_curve](https://gmic.eu/gmic300/thumb/small_video_sine_curve.png)](https://www.youtube.com/watch?v=qp7B0M50MHk)
===

- What if, instead of just rendering 1D curves, we were now interested in the parametric generation of 2D images? This is what the **Patterns / Random Pattern** filter proposes, whose operation is quite original: it generates a random mathematical function `f(z)` (`z` being a complex variable), composed of basic complex functions (`cos()`, `sin()`, `pow()`, …) and operators (`+`, `-`, `*`, `/`, …), by recursively constructing an expression tree. `f(z)` is then evaluated for all the points `z` of the image, located in a rectangular domain, which is itself randomly chosen. The values of `f(z)` are finally transformed into _RGB_ values to determine the colors of all pixels in the image.

===
[![gmic_random_pattern](https://gmic.eu/gmic300/thumb/gmic_random_pattern.png)](https://gmic.eu/gmic300/fullsize/gmic_random_pattern.png)
_Fig.2.5.5. The " Patterns / Random Pattern " filter in action._
===

Note that the construction of the function `f(z)` depends only on the random seed used to generate the expression tree. The figure below illustrates some image renderings obtained with different values of random seeds.

===
[![gmic_random_pattern](https://gmic.eu/gmic300/thumb/gmic_random_pattern_all.png)](https://gmic.eu/gmic300/fullsize/gmic_random_pattern_all.png)
_Fig.2.5.6. Some examples of random patterns generated by the " Patterns / Random Pattern " filter._
===

- Recursive image generation methods can produce original and interesting geometric patterns, and the **Patterns / Triangular Pattern** filter confirms this. It generates images consisting of triangles recursively subdivided in different ways, each with a probability of occurrence adjustable by the user.

===
[![gmic_triangular](https://gmic.eu/gmic300/thumb/gmic_triangular.png)](https://gmic.eu/gmic300/fullsize/gmic_triangular.jpg)
_Fig.2.5.7. The " Patterns / Triangular Pattern " filter in action._
===

As the iterations proceed, more and more complex geometric patterns are formed in the image, as shown in the animation below.

===
[![gmic_triangular_anim](https://gmic.eu/gmic300/fullsize/gmic_triangular_shape_anim.gif)](https://gmic.eu/gmic300/fullsize/gmic_triangular_shape_anim.gif)
_Fig.2.5.8. Visualization of the triangular pattern construction iterations by the " Patterns / Triangular Pattern " filter._
===

By increasing the number of iterations and drawing only the contours of the subdivided triangles, we can generate truly remarkable fractal geometric patterns, given the apparent simplicity of the triangle subdivision algorithm, as illustrated in the following figure. This will give you ideas for tiling your kitchen or bathroom!

===
[![gmic_triangular_patterns](https://gmic.eu/gmic300/thumb/gmic_triangular_patterns.png)](https://gmic.eu/gmic300/fullsize/gmic_triangular_patterns.jpg)
_Fig.2.5.9. Some examples of random recursive triangular subdivisions obtained by the "Patterns / Triangular Pattern" filter._
===

- And speaking of fractals, let's visit the **Rendering / Newton Fractal** filter which allows you to navigate in [Newton Fractals](https://en.wikipedia.org/wiki/Newton_fractal), with a large number of adjustable parameters. These fractals are obtained by trying to find the zeros of a complex function `f(z)` (often a polynomial) by the [Newton method](https://en.wikipedia.org/wiki/Newton%27s_method). This iterative technique builds a sequence that is supposed to converge to one of the zeros of the function. For each (complex) point `z` of the image, we determine its displayed color according to the number of iterations necessary to reach convergence, which generates beautiful fractal geometrical patterns.

===
[![gmic_newton](https://gmic.eu/gmic300/thumb/gmic_newton.png)](https://gmic.eu/gmic300/fullsize/gmic_newton.jpg)
_Fig.2.5.10. The " Rendering / Newton Fractal " filter in action._
===

In _G'MIC-Qt_, the filter allows the user to enter a custom mathematical formula to define the function `f(z)` and its derivatives. It also offers options to colorize the fractal in a personalized way and to easily navigate in the fractal space thanks to its simple but efficient integrated browser. Finally, it extends the principle of calculation to other methods of resolution ([Secant method](https://en.wikipedia.org/wiki/Secant_method) and [Householder method](https://fr.wikipedia.org/wiki/M%C3%A9thode_de_Householder)). And as always with _G'MIC_, it is also possible to script this filter from the command line (with the `gmic` command), to generate for example this type of animations:

===
[![gmic_newton_anim](https://gmic.eu/gmic300/fullsize/gmic_newton_anim.gif)](https://gmic.eu/gmic300/fullsize/gmic_newton_anim.gif)
_Fig.2.5.11. Generation of a zoom in a Newton fractal, scripted with `gmic`._
===

- Still in the "fractal" spirit, the new **Rendering / Tree** filter allows you to generate [fractal trees](https://fractalfoundation.org/resources/fractivities/fractal-trees/), again with many adjustable parameters to tweak as you please.

===
[![gmic_tree](https://gmic.eu/gmic300/thumb/gmic_tree.png)](https://gmic.eu/gmic300/fullsize/gmic_tree.jpg)
_Fig.2.5.12. The "Rendering / Tree" filter in action._
===

In addition to the colors of the trunk and the leaves, the size of the branches and the probability of the branches splitting into several pieces can be adjusted. This allows generation of trees with quite different geometry and looks, as you can see on the figure below.

===
[![gmic_3_trees](https://gmic.eu/gmic300/thumb/gmic_3_trees.png)](https://gmic.eu/gmic300/fullsize/gmic_3_trees.jpg)
_Fig.2.5.13. Examples of tree renderings with different settings, using the "Rendering / Tree" filter._
===

The following video illustrates the use of this filter in _GIMP_ (click on the image below to access the video).
===
[![video_trees.png](https://gmic.eu/gmic300/thumb/small_video_trees.png)](https://www.youtube.com/watch?v=Bsvv0nFFz4w)
===

- Another rendering effect worth highlighting (no pun intended...) is the **Light & Shadows / Guided Light Rays** filter. This filter allows light rays to be emitted from a point source of light, towards or through any shape drawn by the user and defined as an opaque mask placed on a transparent layer above the input image.

===
[![gmic_guided_light_rays](https://gmic.eu/gmic300/thumb/gmic_light2.png)](https://gmic.eu/gmic300/fullsize/gmic_light2.jpg)
_Fig.2.5.14. The " Light & Shadows / Guided Light Rays " filter in action._
===

In the example above, the light rays stop when they meet the pixels of the _G'MIC_ logo. But it is also possible to adapt the filter parameters so that the rays pass through the shape. This is done in the example below, where the user-defined mask corresponds to the glass surface of a living room window.

===
[![gmic_guided_light_rays](https://gmic.eu/gmic300/thumb/gmic_light.png)](https://gmic.eu/gmic300/fullsize/gmic_light.jpg)
_Fig.2.5.15. Light rays synthesized to pass through a user-defined mask._
===

With this filter, it is easy to add custom lighting effects to photographs, as shown in the following example. All you have to do is define the mask of the shape guiding the light rays, and the filter does the rest!

===
[![gmic_guided_light_rays_anim](https://gmic.eu/gmic300/fullsize/gmic_guided_light_rays_anim.gif)](https://gmic.eu/gmic300/fullsize/gmic_guided_light_rays_anim.gif)
_Fig.2.5.16. Adding a side lighting effect with the " Light & Shadows / Guided Light Rays " filter._
===

The following video tutorial shows how to use this filter in _GIMP_:
===
[![video_lightrays](https://gmic.eu/gmic300/thumb/small_video_lightrays.png)](https://www.youtube.com/watch?v=VRiWu_0BZvc)
===

- Finally, to conclude our tour of the new rendering effects, let's end with the **Sequences / Moiré Animation** filter, which takes us into the wonderful world of animation based on the (robust) technologies of the last century, namely: paper sheet and transparent sheet! This filter will indeed allow creation of an animated optical illusion, at low cost, by generating images with a [Moiré effect](https://en.wikipedia.org/wiki/Moir%C3%A9_pattern). From an animation given as input (containing few images), the filter will produce a still image as well as a binary mask containing vertical bars as below:

===
[![gmic_moire](https://gmic.eu/gmic300/thumb/gmic_moire.png)](https://gmic.eu/gmic300/fullsize/gmic_moire.png)
_Fig.2.5.17. Images generated by the " Sequences / Moiré Animation " filter from an animation made of 5 images._
===

The trick is to print the first image on a blank page and the second on a transparent sheet of the same size. By positioning the transparent sheet on the page in an appropriate way, and by moving it laterally, the animation becomes visible. Indeed, the vertical bars printed on the transparent layer allow only one image of the animation to pass through at a time, and these images follow one another as the transparent sheet moves:

===
[![gmic_moire_anim](https://gmic.eu/gmic300/fullsize/gmic_moire_anim.gif)](https://gmic.eu/gmic300/fullsize/gmic_moire_anim.gif)
_Fig.2.5.18. Rendering of the animation when the transparency moves on the printed page._
===

Note that although the number of frames of the animation is indeed limited (in general, less than a dozen, there is obviously no possibility of converting a two-hour film!), there is no reason to limit oneself to grayscale images. The following two figures illustrate, for example, the rendering of a color animation with this filter.

===
[![gmic_moire](https://gmic.eu/gmic300/thumb/gmic_moire2.png)](https://gmic.eu/gmic300/fullsize/gmic_moire2.png)
_Fig.2.5.19. Images generated by the " Sequences / Moiré Animation " filter from a 6-frame color animation._
===

===
[![gmic_moire_anim](https://gmic.eu/gmic300/fullsize/gmic_moire_anim2.gif)](https://gmic.eu/gmic300/fullsize/gmic_moire_anim2.gif)
_Fig.2.5.20. Rendering of the animation when the transparency moves on the printed page._
===

"Your examples are nice, but what does it look like in real life?". Well, the feeling of animation is really present, as you can appreciate in the video below :
===
[![video_moire](https://gmic.eu/gmic300/thumb/small_video_moire.png)](https://www.youtube.com/watch?v=f5plDb_JRq4)
===

To sump up, it's an inexpensive and fun way to create personalized animation materials. Kids, not yet jaded by the _Youtube_ application on their smartphone, will love it!

## 2.6. Keeping up to Date

The set of filters we have just described is only a subset of all the new filters added in the last two years. In particular, there are many "community" filters that sometimes remain in the shadows for some time before being added to the main list of filters (e.g., filters in the **Testing /** category). To make it easier to keep track of these updates, _G'MIC-Qt_ has added the **About / What's New?** function, which lists the recent additions and deletions of filters in the plugin. This list is tailored to the user, as it is based on the user's previous list.

===
[![gmic_whatsnew](https://gmic.eu/gmic300/thumb/gmic_whatsnew.png)](https://gmic.eu/gmic300/fullsize/gmic_whatsnew.jpg)
_Fig.2.6.1. The "About / What's New? filter in action._
===

As a reminder, the **Update Filters** button below the filter drop-down list will allow the plugin to check for new filters and download them if available.

This overview of the new _G'MIC-Qt_ filters is now complete. But more improvements to the plugin are waiting for us!

## 2.7 More and More Host Software

- One of the most important pieces of news in the life of _G'MIC-Qt_ is its availability as a plugin compatible with the [_8bf_](https://fileinfo.fr/extension/8bf) protocol. This _API_ was designed by _Adobe_ in the 90's for the development of plugins for its flagship (and non-free) software _Photoshop_. It is a protocol still in use, despite its great age (and technical limitations). Over the years, this plugin _API_ has even been adopted by many other illustration and photo editing programs. As a result, this _8bf_ version of the _G'MIC-Qt_ plugin can in practice now be used inside many popular _8bf_ protocol-compatible programs, namely: [_Adobe Photoshop_](https://en.wikipedia.org/wiki/Adobe_Photoshop), [_Affinity Photo_](https://en.wikipedia.org/wiki/Affinity_Photo), [_Paint Shop Pro_](https://en.wikipedia.org/wiki/PaintShop_Pro), [_Photoline_](https://www.pl32.com/), [XnView](https://www.xnview.com/), to name a few.

===
[![Greffon G’MIC-Qt sous Affinity Photo](https://gmic.eu/gmic300/thumb/gmic_8bf.png)](https://gmic.eu/gmic300/fullsize/gmic_8bf.jpg)
_Fig.2.1.1. The G'MIC-Qt plugin running under Affinity Photo / Windows._
===

Thanks to [_Nicholas Hayes_](https://github.com/0xC0000054), the author of the [_Paint.NET_](https://www.getpaint.net/) plugin, this _8bf_ version of _G'MIC-Qt_ has been released. This is good news for all users of these proprietary software, who will be able to benefit from a new plugin well supplied with many image processing filters, with the possibility of modifying and improving them, and all this without paying anything (what a change! ☺).

- Another piece of good news is the improved support of the _G'MIC-Qt_ plugin for _GIMP_, especially on _Windows_, where several users reported compatibility problems with the provided `.dll` files when the last version of _GIMP_ was released (_2.10.28_). In addition, thanks to changes made by [Jan Tojnar](https://github.com/jtojnar), the _G'MIC-Qt_ plugin can now be compiled for _GIMP_ version _2.99_ (the name of the development version of _GIMP_ that will become the long-awaited _3.0_). We should also mention the arrival of the _G'MIC-Qt_ plugin for the [_Flatpack_](https://github.com/flathub/org.gimp.GIMP.Plugin.GMic) version of _GIMP_, thanks to the work of [Hubert Figuière](https://github.com/hfiguiere) who packaged it for [_Flathub_](https://github.com/flathub).

- Finally, let's note the expected integration of _G'MIC-Qt_ _3.0_ in the next major version _5.0_ of _Krita_ software, which is planned to be released this December. This integration is planned to be complete and systematic, i.e. _G'MIC-Qt_ will be included by default in _Krita_, and not installed as an external plugin (as it is currently the case). This promises a better integration in _Krita_ and should solve several recurring problems, especially for _Mac_ users. This integration is done by [_amyspark_](https://www.amyspark.me/), with whom we are in contact.

## 2.8. Interface Improvements

The plugin has also seen its graphical interface improved, with in particular:

- A new filter tagging system with colored tags that can be assigned to one or more filters. These colored tags (6 different colors) allow the user to mark certain filters to find them more easily later. Of course, each user decides on the meaning of each color and the use cases are therefore potentially numerous: these tags can be used temporarily for a given session, or alternatively, filters can be marked for a longer period. The plugin interface offers a simple but efficient way of managing these different tags as shown in the animation below:

===
[![gmic_qt_tags](https://gmic.eu/gmic300/fullsize/gmic_qt_tags.gif)](https://gmic.eu/gmic300/fullsize/gmic_qt_tags.gif)
_Fig.2.8.1. Colored "tags" are available to mark filters in the G'MIC-Qt plugin._
===

- A _"Copy G'MIC command to clipboard"_ button, located at the top right of the panel containing the filter controls:

===
[![gmic_qt_clipboard](https://gmic.eu/gmic300/thumb/gmic_qt_clipboard.png)](https://gmic.eu/gmic300/fullsize/gmic_qt_clipboard.png)
_Fig.2.8.2. New button to copy the G'MIC command to the clipboard._
===

This button will delight all scripters: by pressing it, we get the equivalent _G'MIC_ command to be invoked in the terminal for the `gmic` _CLI_ tool, in order to apply the currently selected filter with its current parameter values. For example, here is what the clipboard contains after pressing this button in the example above:
```
fx_spherize 50,4.16,0,58.8136,52.1628,0,0,2,0
```
This string can then be pasted back into a command line call to `gmic`, to get exactly the same effect on other images, or to integrate it into a more complex processing pipeline:

===
[![gmic_qt_clipboard2](https://gmic.eu/gmic300/thumb/gmic_qt_clipboard2.png)](https://gmic.eu/gmic300/fullsize/gmic_qt_clipboard2.png)
_Fig.2.8.3. Application via the terminal of the G'MIC command copied from the G'MIC-Qt plugin, on other images._
===

This is a really handy feature if you write your own processing scripts. You can take advantage of the convenience of the plugin's graphical interface (especially its preview window) to adjust the parameters of a filter, but also the power of the command line to apply batch processing to several dozen or hundreds of image files.

- Among other improvements, _G'MIC-Qt_ has an improved translation system (e.g. a complete French version is planned in the near future), and the _API_ offered by the plugin has been enriched to allow more control by the host software. These improvements are for example used by _G'MIC-Qt_ to offer new [control options](https://github.com/c-koi/gmic-qt/blob/master/STANDALONE.md) via a command line call.

# 3. Improvements to the G'MIC Core

This description of the new features visible in the _G'MIC-Qt_ plugin being completed, let's talk about the other improvements brought by this version _3.0_. A lot of interesting things have been added to the core of the _G'MIC_ project, namely its interpreter and its associated image processing library [_CImg_](http://cimg.eu) (which is also updated to version _3.0_). These new features are certainly less visible, but just as important since they have a potential impact on all the interfaces of the project!

## 3.1. Language and Interpreter Improvements

- Let's start with the feature that required the most development effort, which we already mentioned earlier: the implementation of an internal [machine learning](https://en.wikipedia.org/wiki/Machine_learning) library (`nn_lib`). This library allows the manipulation of generic [neural networks](https://en.wikipedia.org/wiki/Artificial_neural_network) and supports both the network learning phase and the inference phase. This library has been re-implemented from scratch, which represents a really important effort of research, implementation and testing (but it has also been a very instructive work!). `nn_lib` allows the construction in _G'MIC_ of neural networks with convolutional or fully connected modules, pooling modules, residual modules, etc. Several optimizers have been implemented to manage learning (`SGD`, `RMSprop`, `Adam`, `Adamax`) and it is therefore already possible to train networks for some image processing tasks with this new library. The diagram below illustrates, for example, one of the network architectures that has been trained for the new **Repair / Denoise** denoising filter mentioned earlier.

===
[![gmic_denoise_nn](https://gmic.eu/gmic300/thumb/gmic_denoise_nn.png)](https://gmic.eu/gmic300/fullsize/gmic_denoise_nn.jpg)
_Fig.3.1. One of the neural network architectures trained for the new "Repair / Denoise" denoising filter._
===

This is of course only the beginning, but we hope to generalize the use of `nn_lib` to develop new interesting filters in the near future. More technical details about the `nn_lib` library can be found in the [dedicated article]((https://discuss.pixls.us/t/machine-learning-library-in-gmic) on the _G'MIC_ forum.

- Another notable improvement concerns the re-implementation in _G'MIC_ of an extended [_Markdown_](https://en.wikipedia.org/wiki/Markdown) language interpreter: `gmd` (like [_**G**’MIC **M**ark**d**own_](https://gmic.eu/reference/g_mic_markdown.html)). This _Markdown_ rendering engine is now the one used to produce the [reference documentation]((https://gmic.eu/reference/) and the [tutorial pages]((https://gmic.eu/tutorial/), visible on the project web page. It is also used to display the help on the terminal when _G'MIC_ is invoked from the command line (with `gmic -h` for example). The appearance of this new _Markdown_ parser goes hand in hand with an overall improvement of the documentation available for the project.

===
[![gmic_tutorial_reference](https://gmic.eu/gmic300/thumb/gmic_tutref.png)](https://gmic.eu/gmic300/fullsize/gmic_tutref.png)
_Fig.3.1. The new G'MIC Markdown parser is used to render the reference web documentation._
===

- The management of new custom color palettes has been improved, with the introduction of a new [`palette`](https://gmic.eu/reference/palette) command providing 34 predefined color palettes, each composed of 256 _RGB_ colors (some of them recovered from [_CMOcean_](https://matplotlib.org/cmocean/) and [_LOSPEC_](https://lospec.com/palette-list)):

===
[![gmic_palettes](https://gmic.eu/gmic300/thumb/gmic_palettes.png)](https://gmic.eu/gmic300/fullsize/gmic_palettes.png)
_Fig.3.2. Set of color palettes proposed by default in G'MIC._
===

Moreover the _G'MIC_ interpreter user has now the possibility to define and name their own color palettes which will be used in the [`map`](https://gmic.eu/reference/map) or [`index`](https://gmic.eu/reference/_index) commands, used to apply these palettes on color images. These palettes are generally useful for color visualization of scalar image data. For example, the colorization of a [Mandelbrot fractal](https://en.wikipedia.org/wiki/Mandelbrot_set) can be done very simply in _G'MIC_ with the following command line:
```
$ gmic 600,600 mandelbrot -1.0132,-0.316356,-1.00227,-0.305418,512 map amiga7800
```

===
[![gmic_mandelbrot](https://gmic.eu/gmic300/thumb/gmic_mandelbrot.png)](https://gmic.eu/gmic300/fullsize/gmic_mandelbrot.jpg)
_Fig.3.3. Result of the application of the `amiga7800` color palette on a Mandelbrot fractal._
===

- Regarding the rendering of 3D mesh objects, there are two new features: first, the re-implementation of the 3D viewer ([`display3d`](https://gmic.eu/reference/display3d) command) which has been rewritten directly in the _G'MIC_ language and will therefore be easier to maintain and evolve.

===
[![gmic_solenoid](https://gmic.eu/gmic300/thumb/gmic_solenoid.png)](https://gmic.eu/gmic300/fullsize/gmic_solenoid.png)
_Fig.3.4. Overview of the new G'MIC 3D mesh object viewer._
===

Secondly, it is now possible to export a 3D mesh object built in _G'MIC_ (typically with a procedural generation) as an `.obj` file in [_Wavefront_](https://en.wikipedia.org/wiki/Wavefront_.obj_file) format, a simple _ASCII_ format that most 3D modelers can also read. Here, illustrated below, is an example of importing a 3D object generated recursively in _G'MIC_ and re-imported into [_Blender_](https://www.blender.org/), using this _Wavefront_ file format.

===
[![gmic_blender](https://gmic.eu/gmic300/thumb/gmic_blender.png)](https://gmic.eu/gmic300/fullsize/gmic_blender.jpg)
_Fig.3.5. Import in Blender of a 3D object generated by G'MIC in a procedural way._
===

- Still in the field of input-output, we note the appearance or improvement of support for certain file formats, such as those with the extensions `.png`, `.tiff`, `.csv`, `.webp`, `.arw`, `.cr2`, `.nef`, `.dng`, `.heic`, `.avif` (the last two, however, are not activated by default).

- Two new commands [`lorem`](https://gmic.eu/reference/lorem) and [`portrait`](https://gmic.eu/reference/portrait) allow retrieval of random images from two different web services: [_Lorem Picsum_](https://picsum.photos/) and [_ThisPersonDoesNotExist_](https://thispersondoesnotexist.com/). They are quite handy for testing filters quickly on arbitrary images, without having to keep them in local storage. For example, the command :
```
$ gmic +lorem 800 +portrait 800
```
will show you this:

===
[![gmic_lorem_portrait](https://gmic.eu/gmic300/thumb/gmic_lorem_portrait.png)](https://gmic.eu/gmic300/fullsize/gmic_lorem_portrait.jpg)
_Fig.3.6. Overview of the result of the new `lorem`  and `portrait` commands._
===

- Finally, let's note that `gmic`, the command line interface of _G'MIC_, now accepts the definition of [entry points](https://en.wikipedia.org/wiki/Entry_point) in script files with `.gmic` extension, and that we can now make such files executable (with the [Shebang](https://en.wikipedia.org/wiki/Shebang_(Unix))). For example, under _Unix_, the following `test.gmic` file can be made directly executable and launched from a terminal:
```
#!/usr/bin/env gmic
# File 'test.gmic'
echo[] "Hello G'MIC friends!"
```

## 3.2. Improvements to the Mathematical Expression Evaluator

The field of digital image processing is essentially based on mathematical models of images and algorithms that we want to apply. _G'MIC_ has its own mathematical expression evaluator, and this one has also seen many improvements recently. To summarize, more than 40 new mathematical functions have been implemented in this evaluator in the last two years, in order to improve its calculation capacities:
`store()`, `date()`, `begin_t()`, `end_t()`, `merge()`, `f2ui()`, `ui2f()`, `ccos()`, `csin()`, `ctan()`, `ccosh()`, `csinh()`, `ctanh()`, `lerp()`, `maxabs()`, `minabs()`, `argmaxabs()`, `argminabs()`, `da_size()`, `da_insert()`, `da_push()`, `da_remove()`, `da_pop()`, `da_back()`, `isvarname()`, `resize()`, `fill()`, `repeat()`, `set()`, `deg2rad()`, `rad2deg()`, `swap()`, `vargkth()`, `vargmin()`, `vargmax()`, `vargminabs()`, `vargmaxabs()`, `vavg()`, `vkth()`, `vmin()`, `vmax()`, `vminabs()`, `vmaxabs()`, `vmed()`, `vprod()`, `vstd()`, `vsum()`, `vvar()`, `string()`.

More and more complex filters of _G'MIC_ benefit from them. A lot of optimization work has also been done to make this evaluator more and more efficient, in particular by enabling parallel computing when possible. Rather than going into technical details about the implementation and optimization of this module, I demonstrate an example here that shows how this evaluator can be used in a _G'MIC_ pipeline. Here, we want to produce a [Buddhabrot](https://en.wikipedia.org/wiki/Buddhabrot) image, a particular representation of the [Mandelbrot set](https://en.wikipedia.org/wiki/Mandelbrot_set). Below on the left, you can see the content of the `buddhabrot.gmic` file defining the `buddhabrot` command, which produces the image on the right. The _G'MIC_ mathematical expression evaluator is invoked between lines `9` and `27`, which represents then a single math expression. As we can see, this evaluator is able to compile and execute math expressions which are in fact real programs!

===
[![gmic_buddhabrot_all](https://gmic.eu/gmic300/fullsize/gmic_buddhabrot_all.png)](https://gmic.eu/gmic300/fullsize/gmic_buddhabrot_all.png)
_Fig.3.2.1. Generation of a Buddhabrot image with a G'MIC script._
===

The mathematical evaluator is an essential part of the _G'MIC_ framework and will probably continue to evolve in future releases.

# 4. Other Notable Information

Are we done with this article? Not yet! Because working on the _G'MIC_ project obviously means spending a lot of evenings doing research, programming and testing new features, but an important part of the time spent also concerns the management of side items, namely: answering questions on forums or _github_ forges, finding funding to make the project move forward faster, or communicating around the project (for example by writing this kind of articles ☺ !). And on these different points, notable things have happened, since the end of 2019:

- First, we had the privilege of having two grants (two 12-month fixed-term contracts), as part of the _"Platform Support"_ call from the [INS2I Institute](https://www.ins2i.cnrs.fr/en) of the _CNRS_. These financings allowed the consecutive recruitment of two development engineers to work on the _G'MIC_ project. The first one (2018-2019), [Jehan](https://www.gimp.org/author/jehan.html) is a major contributor to _GIMP_. We described his contributions earlier in our [previous report]((https://pixls.us/blog/2019/09/g-mic-2-7-process-your-images-with-style/).

- The second engineer (2019-2020), [Jonathan-David Schröder]((https://github.com/myselfhimself)) has done a lot of work on the implementation of a _G'MIC_ _binding_ for the _Python_ language: [https://pypi.org/project/gmic/](https://pypi.org/project/gmic/). This _binding_ is for the moment frozen at an earlier version (_2.9.2_) of _G'MIC_ and there are still a few corrections to be made, but it is an interface that we would like to bring to the fore. Let's hope that it will attract the interest of new external contributors, experts in _Python_, why not? In 2020, Jonathan-David presented the progress of his work at the [_Libre Graphics Meeting_](https://libregraphicsmeeting.org/2020/en/index.html) which took place online. His presentation is available by clicking on the following link:
===
[![video_lgm2020](https://gmic.eu/gmic300/thumb/small_video_lgm2020.png)](https://www.youtube.com/watch?v=qbJv7QScs3s)
===

In both cases, these financings were fruitful and enabled the opening of the _G'MIC_ project to other horizons (not to mention the pleasure of interacting with these two talented engineers!).

- Another notable news concern the "communication" aspect of the project, with the development and implementation of the **Virtual Artist** touch table. This interactive table shows the principle of style transfer between two images. It can be helpful to introduce the general public to the field of image processing algorithms, with a direct and fun artistic application. It consists of a touch table on which runs a _G'MIC_ script that implements both the user interface and the style transfer algorithm demonstrated. The video below illustrates the operation of this terminal (click on the image to open the link) :
===
[![Virtual Artist](https://gmic.eu/gmic300/thumb/gmic_virtual_artist.png)](https://www.youtube.com/watch?v=us_7SkNajm0)
===

**Virtual Artist** is an interesting way to support scientific interaction with the general public. It was used, for example, during the [_FÉNO 2021_](https://www.normandie.fr/feno) (Festival of Excellence in Normandy), on the _CNRS_ stand.

===
[![feno2021](https://gmic.eu/gmic300/thumb/feno2021.png)](https://gmic.eu/gmic300/fullsize/feno2021.jpg)
_Fig.4.1. GREYC's "Virtual Artist" touch table, in action, at FÉNO 2021._
===

- Additionally, let's note that _G'MIC_ was allowed a short video presentation during the [Fête de la Science 2020](https://www.fetedelascience.fr/), made by the communication department of the [_CNRS_ Normandie delegation](https://www.normandie.cnrs.fr/fr/delegation). Click on the image below to see this video:
===
[![video_fds2020](https://gmic.eu/gmic300/thumb/small_video_fds2020.png)](https://youtu.be/qP_rVje6VFA?t=214)
===

- Still on the subject of communication, we wanted to take the opportunity to announce that the project's mascot "Gmicky" (the little tiger magician) was crocheted by Florence, from [Doomyflocrochet](https://www.doomyflocrochet.com/). Florence makes nice crochet versions of free project mascots, which we invite you to see (and why not, to order).

===
[![Gmicky Crochet](https://gmic.eu/gmic300/thumb/gmicky_crochet.png)](https://www.doomyflocrochet.com/boutique/amigurumi-linux/gmicky-tigre-magicien-mascotte-gmic-en-coton-au-crochet/)
_Fig.4.1: "Gmicky", the mascot of the G'MIC project, made of crochet._
===

- Finally, more generally, for those who would like to dive deeper into the programming of image processing algorithms, let's mention the release of the book [« Le traitement numérique des images en C++ »](https://www.editions-ellipses.fr/accueil/13463-le-traitement-numerique-des-images-en-c-implementation-dalgorithmes-avec-la-bibliotheque-cimg-9782340045965.html) (Éd. Ellipses, 318 pages, in French), which I co-authored with my colleagues from the University of Clermont Auvergne, [Vincent Barra](https://perso.isima.fr/~vibarra/) and [Christophe Tilmant](http://christophe.tilmant.free.fr/), during the lockdown of 2020. You will find a presentation of [_CImg_](http://cimg.eu), the _C++_ image processing library (of which I am the author) and on which most of the _G'MIC_ functionalities are based, as well as various workshops around different image processing themes and applications.

===
[![Book CImg](https://gmic.eu/gmic300/thumb/book_cimg.png)](https://www.editions-ellipses.fr/accueil/13463-le-traitement-numerique-des-images-en-c-implementation-dalgorithmes-avec-la-bibliotheque-cimg-9782340045965.html)
_Fig.4.2. A book to deepen your knowledge of image processing algorithms, with the CImg library, on which G'MIC is based._
===

# 5. What's Next?

Since 2008, _G'MIC_ has been an active project, even if we never defined a very precise roadmap. The development of new functionalities is done according to our free time and opportunities, as well as the research activities in image processing that we carry out in parallel in our research team at the _GREYC_ laboratory. We only hope that this time will not ultimately end up vanishing! Being a researcher or a teacher-researcher sometimes seems to be incompatible with an open source software development activity, which is a very demanding job and at the same time not necessarily very well valued in a career evaluation. It can therefore be tempting to focus on more "profitable" activities from a professional point of view.

On a personal note, I would like to thank the [_GREYC_ laboratory]((https://www.greyc.fr/)) (notably the management, the management service and the _DDA_ service), the [_CNRS_ Normandy Delegation]((https://www.normandie.cnrs.fr/fr/delegation)) (notably the Valorisation service, the Communication service and the _HR_ service), the [_INS2I_ Institute]((https://www.ins2i.cnrs.fr/fr/institut)) of the _CNRS_, the [_LILA_](https://libreart.info/fr/) association, my colleague [Sébastien Fourey](https://foureys.users.greyc.fr/Fr/index.php) (co-lead developer of the project), the members of the [_PIXLS.US_](https://pixls.us/) association (which hosts our [discussion forum]((https://discuss.pixls.us/c/software/gmic/)) as well as all the contributors to the project, the users giving kind, [useful](https://github.com/dtschump/gmic/issues), or even [financial](https://libreart.info/en/projects/gmic) feedbacks. All these people who believed in the project at a given time and in the ability of its developers gave us their support in one way or another. This allowed us to never give up the development of _G'MIC_, since 2008. May they be truly thanked!

# 6. Additional Resources

To properly bring this report to a close, and to satisfy the readers who are still awake and remain hungry, here is a small selection of videos to occupy the long winter evenings that will arrive soon:

- « G’MIC -- Free Image Manipulation Powerhouse ».
===
[![video_gmic_powerhouse](https://gmic.eu/gmic300/thumb/small_video_gmic_powerhouse.png)](https://www.youtube.com/watch?v=1agzsBn7ZE0)
===

- _« G’MIC: An Amazing, Free Plugin »_.
===
[![video_gmic_amazing](https://gmic.eu/gmic300/thumb/small_video_gmic_amazing.png)](https://www.youtube.com/watch?v=p3h8SASo1nI)
===

- _« G’MIC for Krita - Three ways to turn a photograph into a cartoon »_.
===
[![video_krita_cartoon](https://gmic.eu/gmic300/thumb/small_video_krita_cartoon.png)](https://www.youtube.com/watch?v=d0KiBfRLiUQ)
===

- _« G’MIC for Krita - Step by Step tutorial on how to use this amazing FREE image manipulation plugin »_.
===
[![video_krita_gmic](https://gmic.eu/gmic300/thumb/small_video_krita_gmic.png)](https://www.youtube.com/watch?v=pZHS7lgUSM4)
===

- _G’MIC_ presentation at _Libre Graphics Meeting 2021_ : _« How to make 890+ Color LUTs fit in 3.3Mb ? »_.
===
[![video_lgm2021](https://gmic.eu/gmic300/thumb/small_video_lgm2021.png)](https://www.youtube.com/watch?v=YlIDXVDI15E)
===

- _« Using the G’MIC Stylize filter in Krita with flat texture patterns »_.
===
[![video_texture](https://gmic.eu/gmic300/thumb/small_video_texture.png)](https://www.youtube.com/watch?v=BwZNyNo0yjY)
===

- **Final note:** this report is a summary (yes, it is!) of the following detailed release notes: [release notes _2.8_](https://discuss.pixls.us/t/release-of-gmic-2-8), [release notes _2.9_](https://discuss.pixls.us/t/release-of-gmic-2-9), [release notes _3.0_](https://discuss.pixls.us/t/release-of-gmic-3-0). Thanks to _Andy Kelday_ for his help on proof-reading this article!

---
# Additional Links:

* [The G'MIC project](https://gmic.eu)
* [Twitter Feed of the Project News](https://twitter.com/gmic_ip)
---
