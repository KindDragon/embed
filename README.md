# std::embed

The ideas, implementation and proposal surrounding inclusion of a binary resource (from the file system, in particular).

The goal is to provide a way to give access to all of the bytes and data from a file at compile-time, and allow the implementation to embed it in the target program in an implementation-defined manner. Current implementation looks like:

`constexpr std::embedded contents = std::embed_file( "path/to/file" );`

- Magic function implemented by the compiler
- Uses implementation-defined search rules and paths, should by default be local to the file or found along Embed Paths (e.g., `g++ --embed-paths=...`)

## Prior Art

[File String Literals](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0373r0.pdf), by Andrew Tomazos, April 21st, 2016

## Reception and Discussion of Prior Art

Voting from WG21 (the C++ Working Group) on File String Literals indicated that (for some reason) p0373r0 was considered controversial or not-well-received, with the polling language phrased as "Solve the problem of embedding files _somehow_?" ("_somehow_" being the key word here to tell us they were unsure of the proposal, and why it was rejected).

We attempt to deconstruct the voting and possible reasons why the proposal is suitable/unsuitable.

1. Compile Time Contention?

    Voting from another WG21 poll also indicated there was some contention in allowing bytes be available at compile-time: 8 were neutral, 7 were (strongly or regularly) in favor, and 10 were (strongly or regularly) against. Rationale was not given and recollection nor minutes gave ideas.

    It seems very strange to be opposed to having such. Not making it available at compile-time means there's almost no reason to have it as a File String Literal or an embedded resource supported by the standard altogether: making a function that reads from a stream and dumps it into a `std::vector<byte>` or a `std::string` would be more than enough for the runtime case, and everything would go through runtime mechanisms to find such a file and include it... which is precisely the thing people are trying to avoid by using `xxd -i` and other tools in the first place.

    Allowing for embedding at compile-time is one of the primary motivations for this work as it allows the data to not be loaded and dumped into a (heap) variable at program runtime: contents are expected to be served and delivered and already baked into the executable (hence the name "embed"). Ensuring that this is done at compile-time forces any implementation to employ whatever necessary means to make that data available to the user, and if it ends up being used to be baked into the target problem.

    p0373r0 could be construed in allowing these bytes to be presented at compile-time, due to its wording and how it would essentially present an array literal as a return value. Indeed, there is no other way for this **to** be done: runtime loading simply does not make any sense. The availability of the data relative to the file the literal names pointed to would have to be encoded in the final program and loaded from some implementation-defined point: at which point, why would this proposal even exist to begin with?

2. Encoding Issues

    The File String Literals proposal also gets burdened down with having to fight with the difference between "execution character set" and binary, specifying both `F"path/to/file.txt"` and `bF"path/to/file.bin"` to get around the issue. This has caused a lot of friction and -- in my humble opinion -- wasted effort trying to reconcile how to deal with things like potential encodings, line ending cleaning, and other things that hover like a spectre over `<iostream>`. See the [original discussion](https://groups.google.com/a/isocpp.org/forum/#!topic/std-proposals/tKioR8OUiAw/discussion) and the sheer amount of time/messages going back and forth about character set, and the rabbit hole therein. Text versus binary is quite honestly orthogonal to the problem of "I want this data available in my executable from a compile-time / build-time resource".

3. Syntax expectations / issues

    The actual syntax itself is fine, and elegant in many ways. Unfortunately, it presents a cognitive problem to those who write C and C++ programs: `F"path/to/file.txt"` presents the interface as a string: should the value in `const char[] data = F"path/to/file.txt";` be null-terminated? Some say yes, others say no, some say it should be left implementation defined. The first makes some people sad, the second makes other people sad, and the last ruins cross-platform behavior. Either the first or second should be preferred, or it should be made configurable in a standards-defined manner.

## Design Direction and Goals

1. **Binary Only**

    `std::embed` sidesteps the entire mess regarding execution character set and other pitfalls by only dealing with lifting binary bytes, and making them available at compile time. This prevents the issue of having to deal with, e.g. runtime environment and file reading issues versus compile time character set and reading issues. Lifting bytes is also more closely aligned with expected behavior, as many file formats include things that would be stripped away by "text" processing done by typical `<iostream>` behavior (such as newline processing).

2. **Working at Compile Time**

    Working at compile-time means that `std::embed` can be used in `constexpr` contexts. This allows the same benefits presented by using tools like `xxd -i` or manually massaging the data into some form of (raw )string to be included directly into a variable. The return of `std::embed` would provide `constexpr` `operator[]`, `constexpr` `begin`/`end` iterators, and other things to make it a drop-in replacement for the half-hacked preprocessing tools / build-time shenanigans used to accomplish the same task, and allow even more beyond that.

3. **Optional Null Terminator**

    There are many APIs -- old graphics APIs, Operating System APIs, syscalls and others -- which demand a null-terminated series of bytes / units. It would be prudent to have an option passed to `std::embed` that would allow for the data to be appended with a null terminator.

We present the null-terminator option here because they make sense to what implementations and users do/require from their code. Should sufficient use or need for additional options be present, they should be added as additional flags to the `std::embed_options` enumeration.

## Potential Targets

Pre-Rapperswil Mailing Deadline: May 7th, 2018

Rapperswil: June 4th - 9th, 2018

- [x] Contact authors of Prior Art
- [x] Initial Notes and Ideas
- [x] Discussion (Slack, Discord, mailing list, C++ user group)
- [x] Write initial paper for Rapperswil (missing deadline is not an option!): May 7th, 2018
- [ ] GCC Implementation: May 31st, 2018
- [ ] Clang Implementation: May 31st, 2018
- [ ] Submit to LLVM Mailing List (cfe-dev), not for patch review but for suggestions
- [ ] Submit to GCC Mailing List (gcc) (Seems a bit dead in there: perhaps go to GCC IRC first?)
- [ ] Send out for feedback, ask individuals to use branch
- [ ] Attend Rapperswil meeting: June 4th - 9th, 2018
