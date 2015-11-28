//Define prototypes here
void my_example_function(int x, int y);
void ToggleLed(void);

void FunctionManagerSetup(void)
{
    fcnmgr.AddFunction("ToggleLed",  new Delegate0<void>(ToggleLed));//zero arguments
    fcnmgr.AddFunction("example",  new Delegate2<void, int, int>(my_example_function));//two arguments
}

void my_example_function(int x, int y)
{
    Serial.print("I could process numbers: ");
    Serial.print(x);
    Serial.print(" and ");
    Serial.println(y);
}

void ToggleLed(void)
{
    static bool state = false;
    
    state = !state;
    
    digitalWrite(13, state);
}
