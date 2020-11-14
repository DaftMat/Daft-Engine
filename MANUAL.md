# User Manual

## Introduction
After installing and running Daft-Engine, You can observe an empty scene. As you add objects to the scene, you can edit your world.

![edition mode](https://github.com/DaftMat/Daft-Engine/blob/manual/resources/EditionNoSelection.png?raw=true)

Here is what the interface look like, you can refer to this image in the rest of this manual.

## Top menu bar
#### File
In this section, you can load scenes that demonstrates some features of this engine:
- HDR demos
  - open space
  - close space
- Shadow maps demo
#### About
Gives information about the versions of the APIs that were used.

## Central section
Where the scene is drawn.

## North menu bar
This section covers the top menu bar with the scene tree edition and the drawing mode parametrization.

### Edit scene
On the left side of the top menu bar, you can see 3 buttons: `Add object`, `Add light` and `Remove`. 
These will be used to edit the scene tree.

#### `Add object` button
By clicking on it, the combo box will drop and ask for an object type.
Here are the different object types Daft-Engine offers.
- Primitive objects
  - Sphere
  - Torus
  - Cube
  - Cylinder
- B-Spline based objects
  - BSpline
  - BSpline2D
- Reconstructed iso-surfaces
  - Metaballs
  - Procedural caves
- Others
  - Group : an empty object that can contain other objects
  - Custom : load an object from a `.obj` file

#### `Add light` button
By clicking on it, the combo box will drop and ask for a light type.
Here are the different light types Daft-Engine offers.
- Point light
- Spot light
- Directionnal light

#### `Remove` button
Removes the currently selected drawable from the scene tree.

**Note:** a *drawable* can either be an object, a group or a light.

### Parametrize drawing mode
On the right side of the top menu bar, you can see 2 combo boxes with a form label: `Shader` and `Render mode`

#### `Shader` combo box
Currently, the only shader Daft-Engine proposes is a blinn-phong one.

#### `Render mode` combo box
##### Edition
will draw the scene with mesh lines, control grid and control polygons for Lights or B-Splines for example.
##### Rendering
will only draw objects with no lines, no model for lights. the following picture show what rendering mode looks like.

![rendering mode](https://github.com/DaftMat/Daft-Engine/blob/manual/resources/renderingNoSelection.png?raw=true)

## East tree model
This tree model represents the scene. You can select a drawable by clicking on its name in the tree model. The corresponding drawable's mesh will then appear yellow in the central section if the engine is on `edition` mode. Also, the right part of the south section will show the corresponding drawabe's settings that can then be edited from this panel.
The following picture demonstrates it.
 
![drawable selection](https://github.com/DaftMat/Daft-Engine/blob/manual/resources/EditionMBSelection.png?raw=true)

Lastly, you can edit the name of an object by double clicking on its name in the tree model.

**Caution:** naming a drawable the same as an already existing one will result in a crash...

## South section
As explained, the right part of this section will show the currently selected drawable's settings. However, when no object is selected, another setting appears: `Exposure`. Changing it while in edition mode won't do anything, but in the rendering mode, it will brighten or darken the scene as you change the `Exposure` value.