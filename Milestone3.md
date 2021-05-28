# Individual Report for Miledstone 3

## Modifications of Design and Implementation

* (Minor Improvement) Add a new tool function to parse tile string with colours. Besides,
  every string that outputs tiles will now use it so that the functional cohesion of the
  whole project is increased.
* (Minor Improvement) Add a help function `Menu::printHelp()` to show help information
  when typing `help` in the prompt at any time.
* (Major Improvement) The `place` command will now support multiple input now. It uses
  the original syntax to split batch operations with commas (like 
  `place A1,B2 at C3,D4`). It uses `std::vector` to save splitted input, and iterate
  the batch operations using `for`. Therefore, the total time complexity is linear.
* For `GamePlay::placeTile()`, use a different interface to support batch operations,
  and use constant refernces for arguments to reduce unnecessary memory allocations.
* Move some functions declarations for reusing in newly implemented codes.

## Efficiency for enhancements

The analysis here corresponds to the above description one by one.

* Constant time cost for add prefix and suffix.
* We use tail recursion instead of infinite loops to output help information,
  so its performance won't be so bad given compiler's optimizations.
* as we talked above, the total time complexity is linear.

## Several Issues Encountered

* During modifying `placeTile()`, I noticed that the arguments of function doesn't use
  references. For avoiding unnecessary memory allocations, related optimizations has 
  been adapted.
* When calling `Menu::getName()`, a string with space will result to unexpected behaviour
  (not reporting errors but continuing with empty name). This bug has been fixed.