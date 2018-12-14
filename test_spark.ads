package Stack_Package
  with SPARK_Mode
is
   type Element is new Natural;
   type Stack is private;

   function Empty return Stack;
   procedure Push (S : in  Stack; E : Element);
   function Pop (S : in  Stack) return Element;


end Stack_Package;
