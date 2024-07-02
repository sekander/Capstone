# Capstone
Humber Capston Project

Android Framework:

Main-Menu: MenuScreen.java
Functionality Highlights

    Networking: Uses UDP for communication, handling connections, and data transmission.
    Input Handling: Manages touchpad and gamepad inputs for controlling game actions.
    Rendering: Utilizes camera, stage, and debug rendering for visualizing game elements and UI.
The MenuScreen class in this implementation serves as the entry point for the main menu screen of a game, handling UI setup, input processing, rendering, and network connectivity testing using LibGDX and standard Java networking APIs. The class utilizes scene2d for UI layout and interaction, and it integrates with game assets managed by AssetManager. The network connectivity functionality (searchForConnection() method) demonstrates usage of UDP socket communication to verify connectivity to a local subnet.

Network Controller: 
Functionality Summary

The NetworkTest class encapsulates a comprehensive set of features essential for a networked game environment:

    Networking: Utilizes UDP socket communication for real-time data exchange.
    Game Objects: Manages entities and object creation efficiently using PooledEngine and EntityFactory.
    UI and Rendering: Renders game elements and manages UI components using OrthographicCamera, ShapeRenderer, and Stage.
    Input Handling: Manages player inputs from touchpads and gamepads via AndroidController.
    Font and Text Handling: Renders text using various BitmapFont instances.
    Game State Management: Tracks and manages game states using boolean flags.
    Debugging and Utilities: Provides tools for debugging and includes utility methods for data manipulation.

Together, these features enable NetworkTest to create and manage a dynamic, responsive, and interactive game environment, integrating networking capabilities seamlessly with game logic and user interface.

OpenGL Framework:

ECS Componets:
The Component class serves as an abstract base class defining the interface for all components in a system. It mandates that derived classes implement essential functions like initialization (onCreate()), cleanup (onDestroy()), update (update()), and rendering (draw()). The use of std::shared_ptr via the Ref<T> alias ensures safe and efficient memory management of component instances.

This design pattern facilitates modular and extensible software architecture, commonly used in game engines and other complex systems where components need to be managed dynamically and efficiently.

Transform Component:
The TransformComponent class encapsulates properties (position, scale, rotation) necessary to represent transformations of an object in 2D or 3D space. It inherits from Component, implying it can be part of a hierarchical structure typical in game engines. GLM types (vec2, vec3, mat4) facilitate mathematical operations essential for graphics programming. Getter and setter methods provide access to transformation data, and additional functions like transform() likely aid in computing transformation matrices for rendering.

This class is foundational in game development, where managing object transformations efficiently is crucial for rendering and gameplay mechanics.

Render Component:
The RenderComponent class encapsulates rendering functionality using OpenGL, likely for rendering sprites and textures in a game or graphical application. It manages OpenGL objects (VAO, VBO) and provides methods for initializing, rendering, and managing sprites and textures. This class integrates with other graphics-related components (sprite, Texture2D) and utilizes GLM for mathematics, crucial for transformations and rendering in 2D or 3D graphics contexts. The class design allows for flexible rendering of sprites, textures, lines, and squares, supporting various graphical elements typical in game development.

Shader Component:
The ShaderComponent class serves as a wrapper around OpenGL shader functionality, providing methods to load shaders, set shader uniforms, and manage the shader program lifecycle. It abstracts away the complexities of shader compilation and management, making it easier to integrate shaders into a larger application framework. This class would typically be used in conjunction with other rendering components to apply shaders to geometry and achieve various visual effects in an OpenGL-based graphical application.

TextRender Component : 
The TextRenderComponent class encapsulates functionality for rendering text using FreeType and OpenGL. It manages the loading of fonts, pre-compilation of character glyphs, and rendering of text strings. This class would typically be integrated into a larger rendering system to display text within an OpenGL-based graphical application.

Physics Component: 
The PhysicsComponent class integrates Box2D physics simulation into a larger software system, providing functionality to create various types of physics bodies (kinematic, dynamic, static) and edge shapes. It manages Box2D objects and provides methods to update and draw physics bodies, essential for realistic object interactions and simulations in game development or other physics-based applications.

AI Component:
The AIComponent class integrates AI behavior and pathfinding capabilities into a game or simulation system using Box2D for physics and a BFS graph algorithm for pathfinding. It encapsulates methods for AI movement, steering behaviors, and pathfinding operations, providing essential functionalities for controlling AI entities within a game environment.

Network Component:
The NetworkComponent class integrates UDP socket communication, JSON parsing, and basic network management functionalities into a component-based architecture suitable for game development or other interactive applications requiring networked interactions. It provides methods to initialize sockets, send and receive data, manage socket lifecycle, and integrate with other components of the application, enhancing its network capabilities.

Actors:
The Actor class provides a flexible and extensible way to manage components within a game or application. It leverages templates and smart pointers (std::shared_ptr) to handle component addition, retrieval, and removal dynamically at runtime. This design supports a modular approach to entity composition, enhancing code reusability and maintainability in complex systems.

Certainly! Here's an outline of the key features and functionalities of the NetworkComponent class:

    Initialization and Destruction
        Constructor and Destructor: Initialize and clean up the network component, logging status messages upon destruction.

    Socket Management
        initUDPSocket: Creates a UDP socket, binds it to a specified port, and prepares it for communication.
        power_off_socket: Closes a socket connection gracefully, shutting down communication channels.

    Server Functionality
        recieve_send: Handles the core server logic, continuously listening for incoming client messages, managing server state flags (server_listening, connection_established), and responding appropriately.
        Server State Management: Controls server state transitions based on game-specific data (GameData), including connection establishment and termination.

    Data Transmission
        Data Reception: Receives and processes client messages using UDP, updating game data based on parsed JSON inputs.
        Data Transmission: Sends responses back to clients, confirming connection status and transmitting game state information.

    JSON Parsing
        parseJSON: Utilizes RapidJSON library to parse incoming JSON messages, updating game-specific data structures (GameData) with client inputs.
        Error Handling: Detects and logs parsing errors, ensuring robust handling of malformed JSON inputs.

    Logging and Debugging
        Error Reporting: Uses standard output (std::cout) and error stream (std::cerr) for logging important events, errors, and warnings.
        Debug Mode: Conditional compilation (#ifdef _DEBUG) to enable additional logging and debugging messages during development.

    Modularity and Extensibility
        Component Architecture: Integrates with a broader component-based architecture (Component superclass), facilitating modular and scalable application design.
        Component Management: Supports dynamic addition (AddComponent) and removal (RemoveComponent) of components, enhancing flexibility and extensibility.

    Concurrency Considerations
        Threading: Potential for integrating multi-threading to handle concurrent client connections and improve server responsiveness (not fully implemented but suggested).

    Code Organization and Readability
        Header Inclusions: Organizes necessary header files (iostream, thread, etc.) for clear dependencies.
        Function Definitions: Defines functions (onCreate, onDestroy, update, etc.) with clear responsibilities, promoting readability and maintainability.

This outline summarizes the main features and design considerations of the NetworkComponent class, focusing on robust network communication, data management, and error handling in a game development context.

