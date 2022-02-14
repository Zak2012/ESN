# ESN
 A lightweight parser for storing and reading string

### ESN stands for
E - Easy  
S - String  
N - Notation  

You can refer Application.cpp and Example.esn as documentation  
You can just put ESN.cpp along with your other code or compile and make a library file

This project is targeted to those who needs a light weight parser to store/read string

## File Format
- ### Comment
```#Im a comment```  
Parse will ignore text after the '#' character

- ### Key / Value
```Key : Value```  
Correspond to the key and value in the ESN map

- ### Usage of Semicolon
```;```  
Can be use to break a line without enter  
Also can be use at the end of line


## API reference

- ### Map;
```cpp
ESN::Map;

//expands to
typedef std::unordered_map<std::string, std::string> Map;
```

A typedef for ```std::unordered_map<std::string, std::string>```  
which is the core of how this parser work

- ### ReadFile()
```cpp
bool ESN::ReadFile(const std::string &Path, std::string &Dest);
```
Built in file reader

[Parameter]  
[in] Path : A string to the esn file  
[out] Dest : A buffer destination to write the data

[Return Value]  
```true``` if successfully read file and ```false``` if can't read file

- ### SetVariable()
```cpp
void ESN::SetVariable(ESN::Map &Umap, const ESN::Map &Variables);
```
Replace specified string in ESN value with a string specified in Variable map

[Parameter]  
[in/out] Umap : The ESN map got from [```Parse()```](https://github.com/gsproduction727/ESN#parse)  
[in] Variables : Specify what string to replace with what string  

- ### Parse()
```cpp
ESN::Map ESN::Parse(std::string String);
```

[Parameter]  
[in] String : The ESN file content 

[Return Value]  
A ESN map of the values

- ### ToString()
```cpp
std::string ESN::ToString(const ESN::Map &Umap)
```

[Parameter]  
[in] Umap : ESN file value from [```Parse()```](https://github.com/gsproduction727/ESN#parse)

[Return Value]  
A string of assemblied value  

Output format:  
```
A:b;C:d;B:c;D :e;:f;AA:Name;BB:Some Name;
```

- ### PrettyPrint()
```cpp
std::string ESN::PrettyPrint(const ESN::Map &Umap)
```

[Parameter]  
[in] Umap : ESN file value from [```Parse()```](https://github.com/gsproduction727/ESN#parse)

[Return Value]  
A string of assemblied value but prettier  

Output format:  
```
A : b
C : d
B : c
D  : e
 : f
AA : Name
BB : Some Name
```