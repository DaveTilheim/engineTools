#softEngine project
 A game engine made with the SFML framework (C++)

#requirements!
You have to install the SFML framework to use the soft engine.

#Classes descriptions

#1 Application
This abstract class defined your application comportement.
It contains an update abstract method to update all the data of your application
and it contains too a render abstract method to display all the visual features to the screen.
The Application class has 21 event handler methods which permit
you to manage the application events like key pressed / released,
mouse button pressed / released, ...

#2 UpdaterApplication
Inheritance from Application
this class permit to the user app to update all App objects(Entity) implicitely
only if the programmer has give his App objects to the UpdaterApplication instance
with the add method

#3 Entity
Represents an App object (contains a RectangleShape [SFML])
