Proof of Concept
----------------
Basic constexpr idea works: http://coliru.stacked-crooked.com/a/87e7fb5ed7ae9249
Also see informal/poc/ directory

Current Issues with Build System Approach
-----------------------------------------

ben.craig
@ThePhD note that the build system approach for embedding files isn't that hard... but it has big gotchas if you are aiming for portability
I embed some multi megabyte firmware images in kernel binaries.  The build system turns them into a big array of char.
Surprisingly, that file takes a long time to compile and can hit out of memory errors if the compiler is 32 bit
Had to start compressing it to satisfy the compiler

ThePhD
@ben.craig I've had this problem too: too-long initializer lists, strings that were too big, and complex multi-dimensional data all failing in spectacular ways (not to mention shooting the compilation time up by 500%)

UCD Data as initializers (7+ minutes compile time)

HTML Template Strings - Microsoft's Maximum String Literal Limit

Stringification and Embedded Nulls can be a problem for people who are tempted to use with `const char*` without providing size.


Issues with using include path flags
------------------------------------

I'm also still debating on what the search path should be.
local to the file, a la `#include "blah.txt"`, or through the "include paths", ala `#include <blah.txt>`

lillypad
I think I’d prefer local to the file

ThePhD
Right now I have a "search flags" for both, but it feels like something I should get rid of and just leave it local to the file.

lillypad
Otherwise changing compiler flags would change the behaviour of a non-macro function, which would feel kinda weird I think

"Relative to Where?"
--------------------------
k-ballo
sounds more like both, specified as implementation defined, and suggesting without suggestion that it is treated as header paths

lillypad
if you put `std::embed("file.txt")` in a header, and then include that header in a source file, does it look for “file.txt” relative to the header or the source?


ThePhD
:thinking_face: Uh. I think relative to the header.

lillypad
that makes the most sense, but it wouldn’t really work without embed being a macro, i think
since in the end, the header is just copy-pasted into the source
and I don’t think the compiler really knows what is what after pre-processing

ThePhD
After preprocessing most compilers leave in #file directives.

lillypad
aren’t those removed after preprocessing
since those only matter to the preprocessor

k-ballo
those are injected to produce useful diagnostics during the second lexer phase
and I'd imagine they are removed afterwards, but I do not know
in any case, @ThePhD make sure to capture the spirit of this discussion to your paper

k-ballo
consider what `source_location` does


lillypad
Just be careful to not make the thing under-specified
because then no one would use it
e.g. if the specification allowed different compilers to include from completely different paths, since it’s implementation defined

k-ballo
but that's already the case for `#include`

ThePhD
I could tie it to the usage of `__FILE__`.

lillypad
@k-ballo true
@k-ballo But I don’t think that’s a good thing :stuck_out_tongue:

ThePhD
__FILE__ changes based on headers, too. If I make it based off "the implementation-defined, related to `__FILE__`", there's little room for getting it wrong...