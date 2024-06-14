
# G'MIC 3.4.0: Freedom, Stability, Fraternity for Image Processing

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

Also note the arrival of the **Deformations / Square to Circle [alt]** filter, whose purpose is to transform any centered rectangle (or square) in an image into an ellipse (or circle), and vice versa
