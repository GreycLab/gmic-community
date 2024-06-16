
# G'MIC 3.4.0: Image processing, in the prime of its life.

A new version **3.4.0** of [_G’MIC_](https://gmic.eu) (_GREYC’s Magic for Image Computing_) has just been released!

On this occasion, we offer you a description of the recent features added to this free [framework](https://en.wikipedia.org/wiki/Framework) for [digital image processing](https://en.wikipedia.org/wiki/Digital_image_processing), following our [previous dispatch](https://linuxfr.org/news/g-mic-3-2-5-15-ans-de-developpement-pour-du-traitement-d-images-libre-et-reproductible) on this subject (published in May 2023).

[![G´MIC 3.4.0 Teaser](https://gmic.eu/gmic340/thumbs/teaser_small.png)](https://gmic.eu/gmic340/img/teaser.jpg)

_Note: Click on the images to get a full-resolution version, or a corresponding video when the images contain the icon ![Play Video Icon](https://gmic.eu/gmic340/thumbs/icon_play_video.png)_

----

[The G´MIC Project](https://gmic.eu)
[Project Mastodon Feed](https://piaille.fr/@gmic)
[G’MIC Article Series on LinuxFr.org](https://linuxfr.org/tags/g'mic/public)

----

# 1. _G’MIC_ in a Few Words

[_G’MIC_](https://gmic.eu) is an open-source [framework](https://en.wikipedia.org/wiki/Framework) for [digital images](https://en.wikipedia.org/wiki/Digital_image) manipulation and processing, developed within the [_IMAGE_](https://www.greyc.fr/equipes/image/) team of the [_GREYC_](https://www.greyc.fr/) research laboratory in Caen ([_UMR CNRS_](https://en.wikipedia.org/wiki/Joint_Research_Unit) 6072).

It defines various user interfaces for applying a wide range of algorithms to images and signals. The core of the project is a script language interpreter, the [_“G’MIC language”_](https://gmic.eu/reference/overall_context.html), specifically designed to facilitate the prototyping and implementation of new image processing algorithms and operators. Users can apply operators from several hundred already implemented, or write their own processing pipelines and make them accessible in the different user interfaces of the project.

The most popular _G’MIC_ interfaces are: [`gmic`](https://gmic.eu/reference/), a command-line tool (an indispensable complement to [_ImageMagick_](https://www.imagemagick.org/) or [_GraphicsMagick_](http://www.graphicsmagick.org) for processing/generating/analyzing images from the _shell_), the web service [_G’MIC Online_](https://gmicol.greyc.fr/), and especially, the plugin [_G’MIC-Qt_](https://github.com/c-koi/gmic-qt), usable in many digital image editing software such as [_GIMP_](https://www.gimp.org/), [_Krita_](https://krita.org/), [_Paint.NET_](https://www.getpaint.net/), and [_Photoshop_](https://www.adobe.com/products/photoshop.html) (with the help of the [_PLUGIN HOST_](https://plugin-host.eu/) plugin).

[![Preview of the G’MIC-Qt Plugin](https://gmic.eu/gmic340/thumbs/gmic340.png)](https://gmic.eu/gmic340/img/gmic340.jpg) _Fig. 1.1. Preview of the G’MIC-Qt plugin version **3.4.0**, launched from GIMP 2.10, with the “Comicbook” filter selected_.

# 2. What’s New in Version **3.4.0**?

Version **3.4.0** of _G´MIC_ focuses on *stability* and *long-term support*: After more than 15 years of continuous project development, the concepts and code that make up _G´MIC_ have had time to be tested, and we now want to ensure the stabilization of the _APIs_ of the various project components: the _API_ of [`libgmic`](https://gmic.eu/libgmic.html) (to integrate _G´MIC_ features into _C_ or _C++_ code), that of the [*G´MIC-Qt* plugin](https://github.com/c-koi/gmic-qt/blob/master/NEW_HOST_HOWTO.md) (to port the plugin to new hosts), and the syntax of the _G´MIC_ script language. This also implies freezing the parameter settings of the _G´MIC_ commands already available.

Thus, all versions of this *3.4.x* branch will be dedicated to bug fixing and developing features that do not require modification of these project foundations (for example, developing new filters or image processing operators), with the aim of ensuring maximum backward compatibility between these versions. In this sense, version _3.4.0_ represents a milestone in the project's history.

Regarding the general improvements made to the various user interfaces, we can mainly mention:

  - **_G´MIC Online_** (_G´MICol_): This service, which allows applying _G´MIC_ filters to images directly from a web browser, has existed for several years. In 2024, the [_DDA_](https://www.greyc.fr/laboratoire/dda/) (_Application Development and Deployment_) team at the _GREYC_ laboratory initiated a complete overhaul of this service, resulting in a new look, significant user interface improvements (more intuitive widgets, improved preview window, light/dark themes, favorite filter management, ...), and better integration with the _G´MIC_ core to allow the use of recent filters and image processing pipelines.

[![Preview of the _G´MIC Online_ service](https://gmic.eu/gmic340/thumbs/gmicol.png)](https://gmicol.greyc.fr/)
_Fig.2.1. Preview of the revamped G´MIC Online web service released with version 3.4.0 of G´MIC (here with the light theme)._

If you want to try it out, check [_G´MIC Online_](https://gmicol.greyc.fr/), it will be a great opportunity for us to have a real-world test 😱! And don't hesitate to report any issues. In any case, a big thank you to our colleagues in the _DDA_ team for this significant overhaul work!

  - **_G´MIC-Qt_ Plugin**: Over the past year, more than **40 new image processing filters** have appeared in the plugin. Most will be detailed later in this dispatch. We also mention the appearance of a new "Random Parameters" button in the interface, which assigns random values to the parameters of a selected filter, allowing for a quick preview of the possible render variations for a given filter.

[![Random Parameters button in the G´MIC-Qt plugin](https://gmic.eu/gmic340/thumbs/randomize_parameters_fr.png)](https://gmic.eu/gmic340/img/randomize_parameters_en.jpg)
_Fig.2.2. G´MIC-Qt Plugin: The new "Random Parameters" button assigns random values to the selected filter's parameters._

  - **`gmic` CLI Tool**: All filters created by the developer community are now included in the command-line tool executable, meaning there are no longer differences in the number of filters available by default between the _G´MIC-Qt_ plugin and the `gmic` CLI tool (previously, it was necessary to force filter updates with `$ gmic update`). Today, `gmic` has an arsenal of over **4000 functions** to process your images from the command line. Notable efforts have been made to improve the integrated image viewer (command `display`), which has been completely re-implemented to allow viewing different image types within the same interface.

[![Command 'display'](https://gmic.eu/gmic340/thumbs/command_display.png)](https://gmic.eu/gmic340/img/command_display.jpg)
_Fig.2.3. `gmic` CLI Tool: The G´MIC image viewer has been completely re-implemented and allows viewing different image types within the same interface._

This is also the case for the mathematical function or 1D signal viewer (command `plot`), which has been revamped:

[![Command 'plot'](https://gmic.eu/gmic340/thumbs/command_plot.png)](https://gmic.eu/gmic340/img/command_plot.jpg)
_Fig.2.4. `gmic` CLI Tool: The G´MIC viewer for mathematical functions or 1D signals has also been re-implemented._

Everything makes `gmic` a handy tool, even if we limit ourselves to viewing images on the command line.

- **Other Improvements:**
  - The integrated mathematical expression evaluator has evolved significantly: it is one of the essential bricks of the _G'MIC_ language, as it is responsible for evaluating the results of the mathematical operations needed in scripts (needless to say, calculations are done all the time in image processing). This evaluator has been enriched with many functions, especially for the calculation and processing of [vectors](https://en.wikipedia.org/wiki/Vector_(mathematics_and_physics)), [matrices](https://en.wikipedia.org/wiki/Matrix_(mathematics)), and native manipulation of [heaps](https://en.wikipedia.org/wiki/Heap_(data_structure)).
  - Many native (_C++_) functions of the library have been entirely rewritten in the _G'MIC_ language. This will facilitate the evolution and maintenance of these features, as future modifications/improvements will no longer require mandatory updates to the project's binaries.
  - The commands for loading/saving 3D meshes in `.obj` (_Wavefront_) format have been improved, and new commands for processing/creating 3D meshes have emerged (e.g., to visualize the normal vectors at the vertices of a mesh, as illustrated in the video below). And, no, this is not a rotten apple:

[![Example of 3D rendering](https://gmic.eu/gmic340/thumbs/render3d.png)](https://gmic.eu/gmic340/img/render3d.mp4)
_Fig.2.5. The management of 3D meshes within G'MIC has been enriched with new commands._

That's all for the general improvements of the various interfaces offered by the framework. Let's now move on to the details of the new filters and image processing features that have appeared in _G'MIC_ over the past twelve months.

# 3. Details of the New Filters

In this (long) section, we categorize and describe the recent filters by type of use: [Photo Retouching](#toc-31-photo-retouching), [Distortion Filters](#toc-32-distortion-filters), [Degradation Filters](#toc-33-degradation-filters), [Rendering and Texture Filters](#toc-34-rendering-and-texture-filters), and finally [Artistic Effects](#toc-35-artistic-effects).

## 3.1. Photo Retouching

Three interesting filters have appeared in the _G'MIC-Qt_ plugin to help photographers retouch their digital shots.

First, the **Colors / Mixer [Generic]** filter, a color channel mixing filter that offers the possibility to choose from no less than 16 different color spaces/representations for mixing (_[CMY](https://en.wikipedia.org/wiki/CMY), [CMYK](https://en.wikipedia.org/wiki/CMYK), [HCY](https://code.google.com/archive/p/colour-space-viewer/), [HSI](https://www.blackice.com/colorspaceHSI.htm), [HSL](https://en.wikipedia.org/wiki/HSL_and_HSV), [HSV](https://en.wikipedia.org/wiki/HSL_and_HSV), [Jzazbz](https://opg.optica.org/oe/fulltext.cfm?uri=oe-25-13-15131&id=368272), [Lab](https://en.wikipedia.org/wiki/CIELAB_color_space), [Lch](https://sensing.konicaminolta.us/us/blog/understanding-the-cie-lch-color-space/), [OKlab](https://bottosson.github.io/posts/oklab/), [RGB](https://en.wikipedia.org/wiki/RGB_color_spaces), [RYB](https://en.wikipedia.org/wiki/RYB_color_model), [XYZ](https://en.wikipedia.org/wiki/CIE_1931_color_space), [YCbCr](https://en.wikipedia.org/wiki/YCbCr), [YIQ](https://en.wikipedia.org/wiki/YIQ), and [YUV](https://en.wikipedia.org/wiki/YUV)_). This constitutes a good alternative to traditional contrast or color enhancement tools, to retouch photos that might be a bit dull.

[![Filter 'Colors / Mixer (Generic)'](https://gmic.eu/gmic340/thumbs/filter_mixer_generic.png)](https://gmic.eu/gmic340/img/filter_mixer_generic.jpg)
_Fig.3.1.1. The **Colors / Mixer [Generic]** filter enriches the already available arsenal of filters for contrast and color enhancement._

Let's also talk about the **Details / Sharpen [Alpha]** filter, which, as its name suggests, allows for fine detail enhancement in photographs. It is based on an original technique of pyramidal decomposition of the image relative to an [_Alpha blending_](https://en.wikipedia.org/wiki/Alpha_compositing) operator. This technique particularly seeks to minimize the appearance of "halos" near the edges, which is a common artifact encountered with usual detail enhancement filters.

[![Filter 'Details / Sharpen (Alpha)'](https://gmic.eu/gmic340/thumbs/filter_sharpen_alpha.png)](https://gmic.eu/gmic340/img/filter_sharpen_alpha.jpg)
_Fig.3.1.2. The **Details / Sharpen [Alpha]** filter allows for fine detail enhancement in photographs, minimizing the appearance of "halos"._

[![Filter 'Details / Sharpen (Alpha)'](https://gmic.eu/gmic340/thumbs/filter_sharpen_alpha2.png)](https://gmic.eu/gmic340/img/filter_sharpen_alpha2.jpg)
_Fig.3.1.3. "Before/After" details illustrating the interest of the **Details / Sharpen [Alpha]** filter._

Finally, the **Layers / Spatial Blend Multi-Layers** filter allows for merging multiple shots from the same viewpoint into a single image, with the possibility of generating a spatial linear gradient between these different views. For example, one can photograph the same scene at different times of the day (and night) and use this spatial fusion filter to create an image like the one illustrated below, with just a click or two of the mouse:

[![Filter 'Layers / Spatial Blend Multi-Layers'](https://gmic.eu/gmic340/thumbs/filter_spatial_blend_multilayers2.png)](https://gmic.eu/gmic340/img/filter_spatial_blend_multilayers2.jpg)
_Fig.3.1.4. The **Layers / Spatial Blend Multi-Layers** filter allows for merging multiple photographs with an adjustable spatial linear gradient._

(**Credits**: the images used in the figure above are from the video “[_Stunning New York City skyline timelapse: Day to night_](https://www.youtube.com/watch?v=DDo73Njxdqc)” by the YouTube channel “_Rumble Viral_”.)

The following video illustrates the complete process, using the _G'MIC-Qt_ plugin under _GIMP 2.10_:

[![Filter 'Layers / Spatial Blend Multi-Layers'](https://gmic.eu/gmic340/thumbs/filter_spatial_blend_multilayers.png)](https://gmic.eu/gmic340/img/filter_spatial_blend_multilayers.mp4)

## 3.2. Distortion Filters

Let's now move on to a set of new effects available to distort your images in various ways.

First, the **Deformations / Distort [RBF]** filter, which distorts an image based on user-defined key points and an interpolation function of the _RBF_ type ([_Radial Basis Function_](https://en.wikipedia.org/wiki/Radial_basis_function)) whose mathematical formula is user-specifiable.

[![Filter 'Deformations / Distort (RBF)'](https://gmic.eu/gmic340/thumbs/filter_deformations_distort_rbf.png)](https://gmic.eu/gmic340/img/filter_deformations_distort_rbf.jpg)
_Fig.3.2.1. The **Deformations / Distort [RBF]** filter allows for various distortions based on RBFs. Here, specifying the radial basis function phi(r) = log(0.1+r)._

Next, let's mention the arrival of a new category **Map Projection**, which contains 14 different filters dedicated to transforming maps initially in the form of [equirectangular projection](https://en.wikipedia.org/wiki/Equirectangular_projection) (cylindrical equidistant maps) to convert them into other types of projections. This series of filters is a contribution from _Kristian Järventaus_, a member of the [_Cartographers Guild forum_](https://www.cartographersguild.com/showthread.php?t=47591), a forum specialized in cartography.

[![Filters in the 'Map Projection' category](https://gmic.eu/gmic340/thumbs/filter_map_projection.png)](https://gmic.eu/gmic340/img/filter_map_projection.jpg)
[![Filters in the 'Map Projection' category](https://gmic.eu/gmic340/thumbs/filter_map_projection2.png)](https://gmic.eu/gmic340/img/filter_map_projection2.jpg)
_Fig.3.2.2. The new **Map Projection** filter category offers several geographical map projection algorithms._

We also note the arrival of the **Deformations / Square to Circle [alt]** filter, which aims to transform any rectangle (or square) centered in an image into an ellipse (or circle), and vice versa. A very specialized filter, with obviously few apparent applications at first glance, but when you need it, you'll be glad to have it at hand! For example, we used it below to transform a round painting frame into a square frame:

[![Filter 'Deformations / Square to Circle (alt)'](https://gmic.eu/gmic340/thumbs/filter_square_to_circle.png)](https://gmic.eu/gmic340/img/filter_square_to_circle.jpg)
[![Filter 'Deformations / Square to Circle (alt)'](https://gmic.eu/gmic340/thumbs/filter_square_to_circle2.png)](https://gmic.eu/gmic340/img/filter_square_to_circle2.jpg)
_Fig.3.2.3. The **Deformations / Square to Circle [alt]** filter allows converting square or rectangular objects into round or elliptical objects, and vice versa._

Finally, let's conclude this review of the new image deformation filters with the **Deformations / Poincaré Disk** filter. This filter allows you to generate [Poincaré disks](https://en.wikipedia.org/wiki/Poincar%C3%A9_disk), a family of geometric figures based on hyperbolic geometries, as illustrated in the following figure:

[![Filter 'Deformations / Poincaré Disk'](https://gmic.eu/gmic340/thumbs/poincare_disk.png)](https://gmic.eu/gmic340/img/poincare_disk.jpg)
_Fig.3.2.4. Some examples of Poincaré disks, generated by the **Deformations / Poincaré Disk** filter._

But where it becomes interesting is that this filter also allows you to deform images by projecting them onto these very particular geometries:

[![Filter 'Deformations / Poincaré Disk'](https://gmic.eu/gmic340/thumbs/poincare_disk2.png)](https://gmic.eu/gmic340/img/poincare_disk2.jpg)
_Fig.3.2.5. Projection of an image onto a Poincaré disk._

For example, we used this filter (with some homemade modifications) to generate the short animation, "Flyover of the Poincaré Planet," which illustrates the astonishing fractal properties of these geometric oddities:

[![Filter 'Deformations / Poincaré Disk'](https://gmic.eu/gmic340/thumbs/planet_poincare.png)](https://gmic.eu/gmic340/img/planet_poincare.mp4)

## 3.3. Degradation Filters

Sometimes, one seeks to deliberately _degrade_ images, either to simulate a real alteration (such as motion blur, sensor noise, etc.), or in the pursuit of a purely aesthetic effect ([Glitch Art](https://en.wikipedia.org/wiki/Glitch_art)). For these purposes, the following new effects have been added to _G'MIC_:

- The **Rendering / CRT Scanlines** and **Degradations / CRT Phosphors** filters aim to mimic the display of images on [cathode-ray tube (CRT) screens](https://en.wikipedia.org/wiki/Cathode_ray_tube), by simulating two characteristic effects of these types of displays, namely the [Scanline effect](https://en.wikipedia.org/wiki/Scan_line) and [phosphor](https://en.wikipedia.org/wiki/Phosphor) display. These two filters were created in collaboration with [Romain Hérault](https://fr.linkedin.com/in/romain-herault-91a596137), a new contributor (who recently joined _GREYC_).

[![Filter 'Rendering / CRT Scanlines'](https://gmic.eu/gmic340/thumbs/filter_scanline.png)](https://gmic.eu/gmic340/img/filter_scanline.jpg)
_Fig.3.3.1. The **Rendering / CRT Scanlines** filter imitates the typical "Scanline" effect of CRT displays._

[![Filter 'Degradations / CRT Phosphors'](https://gmic.eu/gmic340/thumbs/filter_phosphor.png)](https://gmic.eu/gmic340/img/filter_phosphor.jpg)
_Fig.3.3.2. The **Degradations / CRT Phosphors** filter simulates the phosphor display technique of CRT displays._

- The **Degradations / Blur [Motion]** filter allows synthesizing motion blur, with user-adjustable spline-based trajectories, directly modifiable by altering key points in the _G'MIC-Qt_ preview window, as illustrated in the figure below:

[![Filter 'Degradations / Blur (Motion)'](https://gmic.eu/gmic340/thumbs/filter_blur_motion.png)](https://gmic.eu/gmic340/img/filter_blur_motion.jpg)
_Fig.3.3.3. The **Degradations / Blur [Motion]** filter simulates motion blur._

- The **Degradations / Sloppy Mess** filter is intended for Glitch Art enthusiasts. It's one of the first filters by a new contributor, [Prawnsushi](http://prawnsushi.free.fr/), who recently took an interest in the _G'MIC_ language for filter creation. This effect is a bit slow to compute but offers many parameters and a wide range of different outputs.

[![Filter 'Degradations / Sloppy Mess'](https://gmic.eu/gmic340/thumbs/filter_sloppy_mess.png)](https://gmic.eu/gmic340/img/filter_sloppy_mess.jpg)
_Fig.3.3.4. The **Degradations / Sloppy Mess** filter deliberately creates artistic digital artifacts on your images._

## 3.4. Rendering and Texture Filters

Rendering filters have the particularity of not requiring input images to function, as they create new images (or new layers) from scratch, through [procedural generation](https://en.wikipedia.org/wiki/Procedural_generation).

- The **Rendering / Underwoods** filter, another one created by _Prawnsushi_, is nothing less than an **underwood generator**! One might say it's not very useful, and indeed it's not a filter that will be indispensable for image processors, photographers, or illustrators in their daily work.

But in a way, this filter illustrates the whole philosophy of the _G'MIC_ project: To produce software that fosters **algorithmic creativity**, facilitates the implementation of **all kinds of filters** (useful or less useful), and allows **free sharing** with users. In practice, this filter has the merit of existing, anyone can try it, and it uses very little memory resources (a few dozen bytes, thanks to the compactness of the _G'MIC_ language by design). And moreover, the results are quite cool! And be assured that it will inevitably serve, one day or another, an artist wanting to synthesize an underwood image in two mouse clicks!

[![Filter 'Rendering / Underwoods'](https://gmic.eu/gmic340/thumbs/filter_underwoods.png)](https://gmic.eu/gmic340/img/filter_underwoods.jpg)
[![Filter 'Rendering / Underwoods'](https://gmic.eu/gmic340/thumbs/filter_underwoods2.png)](https://gmic.eu/gmic340/img/filter_underwoods2.jpg)
_Fig.3.4.2. Examples of underwood image renderings by the **Rendering / Underwoods** filter._

- The **Patterns / Reaction-Diffusion** filter synthesizes textures like those encountered in the modeling of [reaction-diffusion systems](https://en.wikipedia.org/wiki/Reaction-diffusion_system).

[![Filter 'Patterns / Reaction-Diffusion'](https://gmic.eu/gmic340/thumbs/filter_reaction_diffusion.png)](https://gmic.eu/gmic340/img/filter_reaction_diffusion.jpg)
_Fig.3.4.3. The **Patterns / Reaction-Diffusion** filter in the G'MIC-Qt plugin._

Again, the interest in this type of filter may seem quite limited. However, it's the perfect example of a texture that can serve as the basis for creating generative art. Take a texture created by this filter, apply some of the other effects available in _G'MIC_ (e.g., the **Deformations / Drop Water** filter), and you're ready to produce fun animations like the one below:

[![Filter 'Patterns / Reaction-Diffusion'](https://gmic.eu/gmic340/thumbs/water_reaction_diffusion.png)](https://gmic.eu/gmic340/img/water_reaction_diffusion.mp4)

- The **Rendering / Spline Spirograph** filter is inspired by the [Spirograph](https://en.wikipedia.org/wiki/Spirograph) game for generating parametric curves, creating intriguing texture and color effects. The presence of the **Random Parameters** button in the _G'MIC-Qt_ plugin is particularly welcome here, to quickly obtain a varied panorama of possible results from this filter!

[![Filter 'Rendering / Spline Spirograph'](https://gmic.eu/gmic340/thumbs/filter_spirograph.png)](https://gmic.eu/gmic340/img/filter_spirograph.jpg)
[![Filter 'Rendering / Spline Spirograph'](https://gmic.eu/gmic340/thumbs/filter_spirograph3.png)](https://gmic.eu/gmic340/img/filter_spirograph3.jpg)
_Fig.3.4.1. The **Rendering / Spline Spirograph** filter and some examples of possible renderings._

This filter also offers an animated output mode, producing several consecutive layers representing different frames of an animation, allowing the synthesis of short videos like this one:

[![Filter 'Rendering / Spline Spirograph'](https://gmic.eu/gmic340/img/filter_spirograph4.gif)](https://gmic.eu/gmic340/img/filter_spirograph2.mp4)

- The **Rendering / ABN Filigrees** filter also knows how to draw interesting parametric curves, inspired this time by the filigrees found on stock certificates or paper money. This filter pays homage to the _American Bank Note Company_, an engraver of financial paper that was active on Wall Street from the mid-19th century until about sixty years ago.

[![Filter 'Rendering / ABN Filigrees'](https://gmic.eu/gmic340/thumbs/filter_abn.png)](https://gmic.eu/gmic340/img/filter_abn.jpg)
_Fig.3.4.4. The **Rendering / ABN Filigrees** filter._

- The **Rendering / Random Signature** filter is also an amusing curve generator: it aims to draw random signatures, as illustrated in the video below:

[![Filter 'Rendering / Random Signature'](https://gmic.eu/gmic340/thumbs/random_signature.png)](https://gmic.eu/gmic340/img/random_signature.mp4)
_Fig.3.4.4. The **Rendering / Random Signature** filter creates random signatures._

Again, a filter whose usefulness cannot be debated: _["It's completely useless, so it's absolutely indispensable!"](https://en.wikipedia.org/wiki/J%C3%A9r%C3%B4me_Bonaldi)_.

- And to finish this section, let's mention the **Rendering / Twisted Rays** filter which, as its name suggests, generates a twisted rays effect. Again, the use of this filter will probably remain quite confidential. But who knows if among the thousands of _G'MIC_ users, there isn't someone who was precisely looking to achieve this particular effect? Well, now they can! ☺

[![Filter 'Rendering / Twisted Rays'](https://gmic.eu/gmic340/thumbs/filter_twisted_rays.png)](https://gmic.eu/gmic340/img/filter_twisted_rays.jpg)
_Fig.3.4.5. The **Rendering / Twisted Rays** filter creates a swirl of rays on your images._

This filter can, for example, be used to create psychedelic animated effects like this:

[![Filter 'Rendering / Twisted Rays'](https://gmic.eu/gmic340/img/filter_twisted_rays2.gif)](https://gmic.eu/gmic340/img/filter_twisted_rays2.gif)


## 3.5. Artistic Effects

To conclude this list of new _G'MIC_ filters, here are some miscellaneous filters grouped under the term "Artistic" (this is generally the term used in image processing software for filters that are hard to categorize…).

- The **Artistic / Stringify** filter decomposes an input image into quantized color blobs and connects the points (subsampled) located on the contours of these blobs with color segments. Again, the rendering may resemble the curves obtained with the Spirograph game.

[![Filter 'Artistic / Stringify'](https://gmic.eu/gmic340/thumbs/filter_stringify.png)](https://gmic.eu/gmic340/img/filter_stringify.jpg)
_Fig.3.5.1. The **Artistic / Stringify** filter creates image abstractions from color segments._

- The **Black & White / Filaments** filter is based on the projection of thousands of particles from one or more edges of the image, with trajectories deformed by the image's contour geometry. The drawing of these thousands of trajectories with semi-transparent colors produces images like these:

[![Filter 'Black & White / Filaments'](https://gmic.eu/gmic340/thumbs/filter_filaments.png)](https://gmic.eu/gmic340/img/filter_filaments.jpg)
[![Filter 'Black & White / Filaments'](https://gmic.eu/gmic340/thumbs/filter_filaments2.png)](https://gmic.eu/gmic340/img/filter_filaments2.jpg)
_Fig.3.5.2. The **Black & White / Filaments** filter transforms your images into sets of deformed filaments._

- The **Arrays & Tiles / Loose Photos** filter simulates an effect of throwing photos haphazardly on a table, so that the content of the photos recreates a global image specified as the filter's input. Many parameters are adjustable (density, size and ratio of photographs, shading parameters, etc.), giving the user a great deal of freedom over the final rendering.

[![Filter 'Arrays & Tiles / Loose Photos'](https://gmic.eu/gmic340/thumbs/filter_loose_photos.png)](https://gmic.eu/gmic340/img/filter_loose_photos.jpg)
_Fig.3.5.3. Example of rendering by the **Arrays & Tiles / Loose Photos** filter._

- The **Rendering / Quick Copyright** filter, which already existed in previous versions, has been re-implemented from scratch. It is a filter facilitating the insertion of a copyright text (or text signature) on a digital image. It now has many parameters to finely adjust the position of the text, its size, font, etc. Combined with the automation capabilities of the _G'MIC_ language, this filter is advantageous for easily inserting text, in a standardized way, on thousands of photographs.

[![Filter 'Rendering / Quick Copyright'](https://gmic.eu/gmic340/thumbs/filter_quick_copyright.png)](https://gmic.eu/gmic340/img/filter_quick_copyright.jpg)
_Fig.3.5.4. The **Rendering / Quick Copyright** filter in action for inserting copyright text on an image._

- Finally, the **Patterns / Random Rectangles** filter transforms an image into a random partition of colored rectangles, giving an abstract image effect, vaguely inspired by the style of some paintings by [Piet Mondrian](https://en.wikipedia.org/wiki/Piet_Mondrian).

[![Filter 'Patterns / Random Rectangles'](https://gmic.eu/gmic340/thumbs/filter_random_rectangles.png)](https://gmic.eu/gmic340/img/filter_random_rectangles.jpg)
_Fig.3.5.5. The **Patterns / Random Rectangles** filter creates a colorful partition of randomly placed rectangles on the image._

Again, one can imagine using this filter to generate textures that could be used to decorate objects, as demonstrated in the animation below (starting from a pure noise image):

[![Filter 'Patterns / Random Rectangles'](https://gmic.eu/gmic340/img/filter_random_rectangles3.gif)](https://gmic.eu/gmic340/img/filter_random_rectangles2.mp4)

# 4. A Software with Varied Uses

As we have tried to show, _G'MIC_ has multiple facets with a wide range of applications. The user community is not limited to digital artists but also includes researchers, programmers, algorithmicians, etc. Below are some other varied uses of the software.

- **Denoising JWST Images:**

In October 2023, we learned from [_M.J. McCaughrean_](https://piaille.fr/@markmccaughrean@mastodon.social), senior researcher at the [_ESA_ (_European Space Agency_)](https://en.wikipedia.org/wiki/European_Space_Agency) (retired in 2024), that _G'MIC_ was used by some people within the _ESA_ to process images from the [_James Webb Space Telescope_](https://en.wikipedia.org/wiki/James_Webb_Space_Telescope) (_JWST_), particularly for attenuating the frequency noise appearing on some images acquired by the telescope (using the **Repair / Banding Denoise** filter, among others).

_G'MIC_ was, for instance, used (among other software) for creating the cover image of the [_Nature_ magazine, vol. 622, issue 7981](https://www.nature.com/nature/volumes/622/issues/7981) on October 5, 2023, as confirmed by _M.J. McGaughrean_ and indicated in [the associated publication](https://www.nature.com/articles/s41586-023-06551-1), of which he is a co-author.

[![Use of G'MIC by ESA](https://gmic.eu/gmic340/thumbs/nature.png)](https://gmic.eu/gmic340/img/nature.jpg)
_Fig.4.1. Use of G'MIC for denoising images of the Herbig-Haro 211 protostar, acquired by the JWST._

For us developers, it was a pleasant surprise to learn this and realize that _G'MIC_ was being used in the field of astrophysics.

- **Creative Coding:**

_G'MIC_ proves to be a valuable ally when seeking to do [creative coding](https://en.wikipedia.org/wiki/Creative_coding), due to its ability to easily generate/manipulate images and its standard library of operators. Over the past year, we have enjoyed exploring its possibilities for algorithmic creation of images and animations, a small selection of which is shown here:

Let's start with this little animation of swirling snowflakes ([source code](https://pastebin.com/02AsBKNg), 30 lines):

[![Snowflake Animation](https://gmic.eu/gmic340/img/snow.gif)](https://gmic.eu/gmic340/img/snow.gif)
_Fig.4.2. Snowflake animation generated by a G'MIC script._

Then let's continue with this amusing variant of the [Rock-Paper-Scissors](https://en.wikipedia.org/wiki/Rock_paper_scissors) game, where each pixel in an image (whose initial random values represent either _0: a rock_, _1: paper_, or _2: scissors_) plays consecutively with its 8 neighbors, keeping the element that won the most. In the second phase, we stylize the sequence of these different label images, again, with the **Drop Water** filter, resulting in the following animation, which we might call _"Hell's Soup"_ ([source code](https://pastebin.com/YXFbiFnu), 30 lines),

[![Rock-Paper-Scissors Game Animation](https://gmic.eu/gmic340/img/rock_paper_scissors2.gif)](https://gmic.eu/gmic340/img/rock_paper_scissors.mp4)
_Fig.4.3. Rock-Paper-Scissors game animation, where all the pixels in an image play simultaneously._

Finally, let's dive back into the wonderful world of [Mandelbrot fractals](https://en.wikipedia.org/wiki/Mandelbrot_set), starting with this rendering of the Mandelbrot set using the [Orbit Trap](https://en.wikipedia.org/wiki/Orbit_trap) technique, allowing the rendering to be mapped with a color image:

[![Rendering of the Mandelbrot Set using the "Orbit Trap" method](https://gmic.eu/gmic340/thumbs/orbit_trap.png)](https://gmic.eu/gmic340/img/orbit_trap.jpg)
_Fig.4.4. Rendering of the Mandelbrot Set using the Orbit Trap method._

Then, with another type of rendering known as [_Buddhabrot_](https://en.wikipedia.org/wiki/Buddhabrot), but here considering complex series of the type `zn+1 = zn^p + c`, and linearly varying the real exponent `p` between 0 and 6 (rather than keeping `p=2` as for the classic Mandelbrot set), to generate each image of the animation below (source code and details [on this page](https://discuss.pixls.us/t/intriguing-shapes-in-buddhabrot-like-fractals)):

[![Buddhabrot Type Rendering for Complex Series with Exponent](https://gmic.eu/gmic340/thumbs/buddhabrot.png)](https://gmic.eu/gmic340/img/buddhabrot.mp4)
_Fig.4.5. Fractal variations around the Buddhabrot._

Note that generating these high-resolution modified _Buddhabrot_ images requires significant computation time (a few minutes per image). I find this animation intriguing: it is quite easy to see/hallucinate familiar shapes when you look closely at some frames of the animation, a bit like when you look at clouds in the sky (if [you think you see](https://discuss.pixls.us/t/intriguing-shapes-in-buddhabrot-like-fractals) in this animation, a bear's head, an old man sitting, a character's silhouette, a dragon's head, ..., then you are not alone in being a bit of a dreamer ☺).

- **Image Conversion for _String Art_**:

[_String Art_](https://en.wikipedia.org/wiki/String_art) is a form of artistic creation characterized by the use of colored threads connected between points (most often nails) to form a pattern or reproduce a photograph (usually portraits). As an experiment, we wrote a _G'MIC_ script that tries to transform a user-selected grayscale input image into a series of instructions to follow to connect numbered nails with a monochrome thread, to reproduce the image as faithfully as possible (considering the constraints specific to this mode of creation):

[![Attempt to use G'MIC for 'String Art'](https://gmic.eu/gmic340/thumbs/string_art.png)](https://gmic.eu/gmic340/img/string_art.jpg)
_Fig.4.6. More or less successful attempt to use G'MIC for String Art._

Can you recognize who is supposed to be represented in the photo below (there is nothing special to win…)? An attempt not necessarily crowned with success, which deserves to be explored further (especially by managing threads of different colors), but which nevertheless illustrates the multiple possibilities for experimentation that the _G'MIC_ framework allows!

- **Other Related Links**:

To conclude, here are some miscellaneous links that demonstrate the versatility of _G'MIC_:

1. **Steganography**: How to hide data in a noise image? The `rand` command can generate [random values with density](https://en.wikipedia.org/wiki/Probability_density_function), meaning their probability density is a function specified by the user. This has, for example, the application of hiding 256x256 images in histograms of 16-bit/channel noise images, as [detailed on this page](https://discuss.pixls.us/t/new-function-rand-pdf-random-values-following-a-custom-distribution).

2. **Artistic Galleries**:
[_Ivelieu_](https://deviantart.com/ivelieu/gallery) and [_Gannjondal_](https://deviantart.com/gannjondal/gallery) are two artists on the _Deviant Art_ site who sometimes use _G'MIC_ in their artistic creation process. Take a look at their respective galleries, it's worth it!

[![Images from Ivelieu's gallery](https://gmic.eu/gmic340/thumbs/ivelieu.png)](https://gmic.eu/gmic340/img/ivelieu.jpg)
_Fig.4.7. Some works by Ivelieu / Deviant Art._

[![Images from Gannjondal's gallery](https://gmic.eu/gmic340/thumbs/gannjondal.png)](https://gmic.eu/gmic340/img/gannjondal.jpg)
_Fig.4.8. Some works by Gannjondal / Deviant Art._

3. We learned from _Gilles Caulier_ that the next version of the photo management program _digiKam_ 8.4.0 [will include a _G'MIC_ processing tool](https://www.reddit.com/r/kde/comments/1d67s1d/next_digikam_840_photo_manager_program_will/) within the _Batch Queue Manager_, which will allow _digiKam_ users to integrate _G'MIC_ filters into their post-processing workflows.

4. [_Thiojoe_](https://www.thiojoe.com/) is a YouTuber who produces videos about technology and is a programmer in his spare time. He started developing a free tool based on _G'MIC_ to easily generate animations, a tool that you can [find here](https://github.com/ThioJoe/Gmic-Animation-Tools). It only works on _Windows_ for now, but we'll keep an eye on it.

5. Finally, let's mention the _YouTube_ channel of [_JustCallMeInsane_](https://www.youtube.com/@JustCallMeInsane/search?query=g%27mic), a digital illustrator using _Krita_. She recently made a series of videos exploring the different categories of filters in the _G'MIC-Qt_ plugin for _Krita_. We hope in passing that the _Krita_ development team, which manages its own version of the plugin, will be able to update it quickly.

And that's it for the "few" news around the _G'MIC_ project and its new version _3.4.0_.

# 5. Conclusions

We could summarize this report by saying that the _G'MIC_ project "continues its journey".

_G'MIC_ remains, of course, a modest project, developed and maintained by a small team (of enthusiasts), but with a growing number of users and increasingly varied usage feedback. This framework has the chance to be developed within the _GREYC_, a public research laboratory, supported by the laboratory's supervisors (the _CNRS_ "Computer Science" institute, the University of Caen, and _ENSICAEN_), and encouraged by the laboratory's management.

And even if most of the development on this project has probably already been done (more than 15 years of development after all), we are confident that _G'MIC_ will continue to evolve; in any case, we will try, as long as it remains useful to image processors of all kinds!
