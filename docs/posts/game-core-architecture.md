# Game Core Architecture

Lots of programmers, myself included, started writing code with the goal of writing our own game. Maybe it was [The Legend of Zelda](http://en.wikipedia.org/wiki/The_Legend_of_Zelda), [Super Mario](http://en.wikipedia.org/wiki/Super_Mario), [Call of Duty](http://en.wikipedia.org/wiki/Call_of_Duty), or [Minecraft](http://en.wikipedia.org/wiki/Minecraft) that served as the initial inspiration, but at some point you think, "Okay, so I know what I want to make, but how do I do it?" Tutorials to get started are all over the internet, showing everything from fancy 3D graphics to physics to audio, but most of them gloss over how it all fits together. For me, I solved this problem with a little help from an awesome book called [Game Coding Complete](http://www.amazon.com/Game-Coding-Complete-Fourth-Edition/dp/1133776574) by [Mike McShaffry](http://en.wikipedia.org/wiki/Mike_McShaffry) (and others). I studied the book for weeks, then weeks turned into months, months into years, then I got a newer edition. Right now, I'm starting a new project, code name [Phoenix](https://github.com/everettcaleb/phoenix), that is available on [GitHub](https://github.com/everettcaleb/phoenix) for all to download, learn from, use, and when it's done, to play. If you feel inclined to contribute, feel free to fork the repository and contribute. For the rest of you, I'm going to write a series of articles going through the process of building the project. This is the first, and it will talk about the core of the project around which everything else is built. Some of the components may sound familiar to readers of GCC, because its code served as the inspiration for many of the architectural decisions that I made.

For a snapshot of the project code at the time of the writing of this post, [check this tag out](https://github.com/everettcaleb/phoenix/releases/tag/v0-post1).

## Key Concepts

- Identifiers
- Component Model
- Events
- Publish-Subscribe Pattern
- OS Abstraction

### Identifiers

In the project, I created two enumerations that serve as collections of identifiers. Identifiers are basically just numbers that represent some type or instance of some object. Here's an example from code:

<div class="gist">https://gist.github.com/everettcaleb/31e0099c68580df62b8f</div>

As you can see, each keyword is associated with a number. The purpose for using an `enum` instead of `#define` or `const` is that, when the enumeration name is used, tells the compiler that it should only allow values within the `enum` statement. The reason I have `: unsigned int` after the `enum` part is to tell the compiler that the enumeration's value should be stored as an `unsigned int`. I'm sure the code snippet raises at least one question, so I'll answer them pretty quick.

**Why are you using an enumeration? Didn't Mike say to use hashes in his book?**  
There were a few reasons why I decided not to use hashes. First of all, there's no perfect solution, and using an enumeration exchanges compilation speed for runtime performance. The computer I use for development is more than capable of compiling even huge (millions of lines) programs in less than 5 minutes. As this is an open-source and free project, there's no huge deadline or anything to really worry about so I prefer the simplicity of using numbers over hashed strings. Hashes are also notoriously difficult to debug unless you store the original string alongside it (which is possible, but obviously carries its own penalty). For the purpose of having a quickly expandable system, I agree with Mike's method, but personally I like numbers better because of my familiarity with database systems and lookup tables.

### Component Model

I might get some groans from the more experienced Windows programmers out there, but I really like some of the ideas that make up [COM](http://msdn.microsoft.com/en-us/library/windows/desktop/ms694363%28v=vs.85%29.aspx). Here's what I like about it:

- Functionality is abstracted as interfaces
- It allows sets of functionality to be requested
- You don't have to know how the functionality is implemented to use it

Microsoft's COM objects don't necessarily work exactly like that, but that is what I was aiming for in writing the component model in Phoenix. Basically, the whole system revolves around the storage of "components" which are basically raw pointers, an identifier that describes them, and possibly a function to clean up after them.

<div class="gist">https://gist.github.com/everettcaleb/ff624ad85010adc046c7</div>

The code above is an excerpt from `ComponentManager.h`. Basically, it defines a class that stores a stack (so that when we unwind it, components are released in reverse order) of "components". In order to make a component available throughout the game, you call `registerComponent()` (or the `...OnHeap()` variant). After that, any time you call the `ComponentManager`'s `queryComponent()` method, it will retrieve the component with the specified identifier, regardless of where it was registered in the program. There's some code in there to allow components to be loaded across dynamic library boundaries as well, but it's not quite finished yet.

### Events & Publish-Subscribe Pattern

The goal of the `EventManager` in Phoenix is to hide the process of gathering and distributing OS or component events. In Windows desktop applications, for example, OS events arrive through the [Window Procedure function](http://msdn.microsoft.com/en-us/library/windows/desktop/ms632593%28v=vs.85%29.aspx). On another system, such as iOS, this is not the case. To make the process easier and to hide what needs the events from the event handling code, I use a pattern similar to the [Publish-Subscribe](http://en.wikipedia.org/wiki/Publish%E2%80%93subscribe_pattern) pattern. Basically, any events that need to be distributed are sent to the `EventManager` instance which then distributes them to the `IEventSubscriber` instances which are responsible for deciding whether they are interested in the particular event.

<div class="gist">https://gist.github.com/everettcaleb/dbae0bced6b46e5a8462</div>

As you can see, there are functions to register and unregister subscribers as well as to publish and queue events. The event queue/publish code is similar to how components are handled because they can have an associated "finalizer" that is for cleaning up any custom memory allocations that are used by the particular event.

### OS Abstraction

The main goal of the game core architecture that I've developed is to hide the operating system as much as possible and as simply as possible since the goal of the project was to develop a game that runs on Windows, Mac, and other platforms. If you look in the [win32](https://github.com/everettcaleb/phoenix/tree/v0-post1/Phoenix/win32) folder of the project, you can see how I've implemented some of the OS specific code for Windows. It will be easy to port the core to another platform because all you'd have to do is reimplement the components for your target platform. No component associations are hard-coded, any component interfaces are expected to run without OS specific code unless they only exist as a dependency for OS specific implementation code.

## Conclusion

That's all for this post, I'll write more as I make more progress in the project.
