Programming Style Guideline
---------------------------

#### Naming 

  The style for writing code is CamelCase, without Hungarian Notation ( not specifing the type of variable, only for standart Windows parameters or functions).
  
  Names should contain at least minimum idea about what identificator means, like `buttonArray` or `winClass`. Short names will be used for little scopes (like `i` and `j` for loops) or for things that are widely used like `ps` (`PAINTSTRUCT` variable)


* `globals` should be prefixed with 'g_' and must be used with caution (preferably they should not exceed the file scope)

* `static` function variables should be prefixed with 's_'

* `class members`, static and non-static, should NOT be prefixed with 'm_' or 's_'

* `variable` names - camelCase starting with a lowercase letter

* `function` and _class_ names - CamelCase starting with a capital letter

* `#define`'s - SNAKE_CASE, all caps



#### Indentation and braces

* Indent with tabs of size 4

* ALWAYS use braces in cases like `if`'s with one statement

* For `if`'s with one short statement it is possible to use the following:
```
if (condition) { SomeFunction(); }
```

* Use 'Allman' indentation and braces style:
```
if (condition)
{
	// code
}
```


#### Other

* ~~goto~~

* Use prefix increment/decrement (`++i`) operators instead of postfix (`i++`), except for special cases
