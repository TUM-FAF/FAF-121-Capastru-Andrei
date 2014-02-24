Programming Style Guideline
---------------------------

#### Naming 

  The style for writing code is CamelCase, without Hungarian Notation ( not specifing the type of variable, only for standart Windows parameters or functions).
  
  Names should contain at least minimum idea about what identificator means, like `buttonArray` or `winClass`. Short names will be used for little scopes (like `i` and `j` for loops) or for things that are widely used like `ps` (`PAINTSTRUCT` variable).

  `global` variables will be prefixed with 'g_' ( `g_buttonArray` ).
  
  `static` variables will be prefixed with 's_' ( `s_buttonArray` ).

  `functions` will start with a capital letter ( `DrawButtons` ).

  `#define`s will be written in snake_case, all caps. ( `IDC_MAIN_BUTTON`).


#### Indentation

  Indent size 4 (VisualStudio default).

#### Braces

  I will use them always, even if there is only one instruction. `if` (//something) {  //doSomething }
  
  If there's more than one intruction, `Allman` style will be used:
  
  `if` (...)
  
  {
      ...
  }
#### Increment and decrement
  
  Always will be used `i++` and `i--`, `i+=someNumber` and `i-=someNumber` instead of `i = i + someNumber`.
