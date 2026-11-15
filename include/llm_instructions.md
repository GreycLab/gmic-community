# A Reminder of Best Practices for Coding G'MIC Filters

1. Use two spaces for each level of indentation.
2. When you specify mathematical expressions enclosed in double quotes while using the `fill` and `eval` commands, you are allowed to write expressions across multiple lines and include spaces between operators. Use these features to make your code clearer and more readable.
3. To clone an image from the stack and place the clone at the end of the list, simply write `[n]`, where `n` is the index of the image to be cloned.
4. It is not necessary to use `{}` around an expression evaluated as part of a control statement that evaluates to a Boolean. For example, you can write `if round(x)>=pi` directly, rather than `if {round(x)>=pi}`.
5. In G'MIC, a blank character acts as a separator between items, so you generally shouldn't include spaces in arguments or variable assignments. For example, `var = 3` is incorrect, while `var=3` is correct.
6. When assigning a value to a variable that requires a calculation, it is best to use the `var:=` notation rather than `var={...}`. For example, `x:=round(pi)` is preferable.
7. In recent versions of G'MIC, the `endl` command no longer exists; it has been replaced by `done` (or `}`, which is equivalent).
8. To process each image in the list individually, use the `foreach { ... }` construct instead of `repeat $! l[$>] done done`.
9. Do not include a `Random Seed` parameter for the filters you implement, unless you are certain that the rendering displayed in the preview window will be exactly the same as the final rendering once the filter is applied.
