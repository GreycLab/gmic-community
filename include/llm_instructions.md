# A Reminder of Best Practices for Coding G'MIC Filters

1. Use English for the names of filters, parameters, variables, and comments in the code.
2. Use two spaces for each level of indentation.
3. When you specify mathematical expressions enclosed in double quotes while using the `fill` and `eval` commands, you are allowed to write expressions across multiple lines and include spaces between operators. Use these features to make your code clearer and more readable.
4. In a mathematical expression, if you need to divide a term by `100` , use the `%` suffix instead of writing `/100`. For example, write `x%` instead of `x/100`.
5. To apply a command to an existing image and get a new image at the end of the list as the result, use the prefix `+` before the command name. E.g., `+resize[0] 300,100`. If you just want to clone an existing image and place the clone at the end of the list, simply specify `[n]`, where `n` is the index or name of the image to be cloned.
6. It is not necessary to use `{}` around an expression evaluated as part of a control statement that evaluates to a Boolean. E.g., you can write `if round(x)>=pi` directly, rather than `if {round(x)>=pi}`.
7. In G'MIC, a blank character acts as a separator between items, so you shouldn't include spaces in arguments or variable assignments. E.g., `var = 3` is incorrect, but `var=3` is correct.
8. When assigning a value to a variable that requires a calculation, it is best to use the `var:=` notation rather than `var={...}`. E.g., `x:=round(pi)` is preferable.
9. In recent versions of G'MIC, the `endl` command no longer exists; it has been replaced by `done` (or `}`, which is equivalent).
10. To process each image in the list individually, use the `foreach { ... }` construct instead of `repeat $! l[$>] done done`.
11. Do not include a `Random Seed` parameter for the filters you implement, unless you are certain that the rendering displayed in the preview window will be exactly the same as the final rendering once the filter is applied.
12. When defining the filter settings, the three first lines should always be:
~~~
#@gui : Description = note{"<span color="#EE5500"><b>Description:</b></span> \
# A one-line description of what the filter does. Keep it short and concise.
#@gui : "}, sep = separator()
~~~
13. When defining the filter settings, the two last lines should always be:
~~~
#@gui : sep = separator()
#@gui : note = note("<small>Author: <i>Author Name</i>.      Latest Update: <i>YYYY/MM/DD</i>.</small>")
~~~
where `YYYY/MM/DD` must be replaced by the date of the day.
