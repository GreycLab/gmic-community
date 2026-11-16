# A Reminder of Best Practices for Coding G'MIC Filters

## General rules
1. Use English for the names of filters, parameters, variables, and comments in the code.
2. Use two spaces for each level of indentation.
3. If you need to test the execution of your code with a recent version of G'MIC, you can install the G'MIC binding for Python using `pip install gmic`.

## Command pipeline
4. In a G'MIC pipeline, a blank character acts as a separator between items, so never include spaces in list of arguments or variable assignments. E.g., `var = 3` is incorrect, but `var=3` is correct. If spaces are needed in argument (e.g. a string), embrace the argument with double-quotes.
5. To process each image in the list individually, use the `foreach { ... }` construct instead of `repeat $! l[$>] done done`.
6. To apply a command to an existing image and get the result a new image at the end of the list, use the prefix `+` before the command name. E.g., `+mirror[0] x`. If you just need to clone an existing image and place it at the end of the list, simply use `[n]`, where `n` is the index or name of the image to be cloned (command `dup` does not exist).
7. It is not necessary to use `{}` around an expression evaluated as part of a control statement that evaluates to a Boolean. E.g., you can write `if round(x)>=pi` directly, rather than `if {round(x)>=pi}`.
8. When assigning a value to a variable that requires a calculation, best use `var:=` rather than `var={...}`. E.g., `x:=round(pi)` is preferable.
9. In recent versions of G'MIC, the `endl` command no longer exists; it has been replaced by `done` (or `}`, which is equivalent).
10. Use command shortcuts when needed (e.g. `r` for `resize`, `f` for `fill`, `c` for `cut`, `n` for `normalize`, `s` for `split`, etc.)

## Mathematical expressions
11. When you specify mathematical expressions enclosed in double quotes (e.g. while using the `fill` and `eval` commands), you are allowed to write expressions across multiple lines and include spaces between operators. Use these features to make your code clearer and more readable.
12. In a mathematical expression, if you need to divide a term by `100` , use the `%` suffix instead of writing `/100`. E.g., write `x%` instead of `x/100`.

## Definition of filter parameters and GUI
13. When defining the filter GUI, the three first lines after the filter definition itself must be:
~~~
#@gui : Description = note{"<span color="#EE5500"><b>Description:</b></span> \
# A one-line description of what the filter does. Keep it short and concise.
#@gui : "}, sep = separator()
~~~
14. When defining the filter GUI, the two last lines must be:
~~~
#@gui : sep = separator()
#@gui : note = note("<small>Author: <i>Author Name</i>.      Latest Update: <i>YYYY/MM/DD</i>.</small>")
~~~
where `YYYY/MM/DD` must be replaced by the date of the day.
15. Parameter names must be capitalized as in an English title, following APA conventions
16.  Do not include a `Random Seed` parameter for the filter unless you are certain that the rendering displayed in the preview window will be roughly the same as the final rendering once the filter is applied.
17. When defining a `choice()` parameter, if the default choice is the first item, you don't need to specify a `0` as the first argument.
18. If it might be useful to randomize a parameter so that the user can randomly explore the filter's parameter space, prefix the parameter name with `~`. E.g., `~color(255,255,255)`.
