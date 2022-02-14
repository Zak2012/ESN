#include "ESN.hpp"

bool ESN::ReadFile(const std::string &Path, std::string &Dest)
{
    std::ifstream infile(Path);
    if ( infile.fail() )
    {
        return false;
    }

    std::string line;
    std::stringstream ss;
    while( getline(infile, line) )
    {
        if ( !line.empty() )
        {
            ss << line << "\n";
        }
    }
    infile.close();
    Dest = ss.str();
    return true;
}

// replace a substring inside umap value with a value
void ESN::SetVariable(ESN::Map &Umap, const ESN::Map &Variables)
{
    // all non valid character
    const char StringDelimiter[3] = {' ','\t',':'};
    for (auto i : Umap)
    {
        std::string UmapTitle = i.first;
        std::string UmapContent = i.second;

        for (auto j : Variables)
        {
            std::string VariableTitle = j.first;
            std::string VariableValue = j.second;

            // find and replace all substring
            std::size_t start_pos = 0;
            while((start_pos = UmapContent.find(VariableTitle, start_pos)) != std::string::npos) {
                UmapContent.replace(start_pos, VariableTitle.length(), VariableValue);
                start_pos += VariableValue.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'

                std::size_t LastLetterKeyPos = UmapContent.find_last_not_of(StringDelimiter);
                if ( LastLetterKeyPos != std::string::npos )
                {
                    UmapContent = UmapContent.substr(0, LastLetterKeyPos - 0 + 1);
                }
            }

            Umap[UmapTitle] = UmapContent;
        }
    }
}

ESN::Map ESN::Parse(std::string String)
{
    // replace semicolon with new line
    std::replace( String.begin(), String.end(), ';', '\n');

    // split string from the new line
    std::vector<std::string> StringArr;
    std::stringstream ss(String);
    std::string CurLine;

    while (getline (ss, CurLine, '\n')) {
        StringArr.push_back (CurLine);
    }

    ESN::Map ParsedString;
    // all non valid character
    const char StringDelimiter[3] = {' ','\t',':'};

    for ( unsigned int i = 0; i < StringArr.size(); i++)
    {
        // find comment '#'
        std::size_t CommentPos = StringArr[i].find('#');
        if ( CommentPos != std::string::npos )
        {
            StringArr[i] = StringArr[i].substr(0, CommentPos);
        }

        // find the colon to separate key and value
        std::size_t ColonPos = StringArr[i].find(':');
        if ( ColonPos != std::string::npos )
        {
            std::string Key;
            std::string Val;

            // find a valid key
            // "    Key : Value"
            // The key = "Key"
            std::size_t FirstLetterKeyPos = StringArr[i].find_first_not_of(StringDelimiter);
            if ( FirstLetterKeyPos != std::string::npos )
            {
                std::string tKeyString = StringArr[i].substr(0, ColonPos);
                std::size_t LastLetterKeyPos = tKeyString.find_last_not_of(StringDelimiter);
                if ( LastLetterKeyPos != std::string::npos )
                {
                    Key = StringArr[i].substr(FirstLetterKeyPos, LastLetterKeyPos + 1);
                }
            }

            // find a valid Value
            // "Key  :   Value  " 
            // The value = "Value"
            std::size_t FirstLetterValPos = StringArr[i].find_first_not_of(StringDelimiter, ColonPos);
            std::size_t LastLetterValPos = StringArr[i].find_last_not_of(StringDelimiter);
            Val = StringArr[i].substr(FirstLetterValPos, LastLetterValPos - FirstLetterValPos + 1);
            
            ParsedString[Key] = Val;
        }
    }
    return ParsedString;
}

std::string ESN::ToString(const ESN::Map &Umap)
{
    // Store string inside a vector
    std::vector<std::string> StringVector;
    for (auto it : Umap)
    {
        std::stringstream ss;
        ss << it.first << ":" << it.second << ";";
        StringVector.push_back(ss.str());
    }

    // Reverse the vector so it appear in the 'correct' order
    std::stringstream ss;
    for (auto i = StringVector.rbegin(); 
        i != StringVector.rend(); ++i )
    {
        ss << *i;
    }
    return ss.str();
}

std::string ESN::PrettyPrint(const ESN::Map &Umap)
{
    // Store string inside a vector
    std::vector<std::string> StringVector;
    for (auto it : Umap)
    {
        std::stringstream ss;
        ss << it.first << " : " << it.second << "\n";
        StringVector.push_back(ss.str());
    }

    // Reverse the vector so it appear in the 'correct' order
    std::stringstream ss;
    for (auto i = StringVector.rbegin(); 
        i != StringVector.rend(); ++i )
    {
        ss << *i;
    }
    return ss.str();
}