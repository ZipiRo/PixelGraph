struct Glyph
{
    std::vector<Vector2> vertices;
    std::vector<unsigned int> indices;
    float advance; // Spaceing after glyph;
};

using json = nlohmann::json;

void CreateFontTable(const std::string &file, std::map<char, Glyph>& glyphs)
{
    if (file.substr(file.find_last_of(".") + 1) != "f2p") {
        std::cerr << "Invalid file extension. Expected '.f2p'.\n";
        return;
    }

    std::ifstream FILE(file);
    if(!FILE)
    {   
        std::cerr << "Failed to open font file: " << file << std::endl;
        return;
    }

    json fontData;
    FILE >> fontData; 

    if(!fontData.contains("glyphs"))
    {
        std::cerr << "Invalid font file format: Missing 'glyphs' key" << file << std::endl;
        return;
    }

    for(const auto &entry : fontData["glyphs"].items())
    {
        char character = entry.key()[0];
        const auto &glyphData = entry.value();

        Glyph glyph;

        for(const auto &vertex : glyphData["vertices"])
        {
            float x = vertex[0];
            float y = vertex[1];
            glyph.vertices.emplace_back(Vector2(x, y));
        }

        for(const auto  &index : glyphData["indices"])
        {
            glyph.indices.emplace_back(index);
        }

        glyph.advance = glyphData["advance"];

        glyphs[character] = glyph;
    }
}
 
class Font
{
private:
    std::map<char, Glyph> glyphs;

public:
    Font() {};
    Font(const std::string &file);

    void SetFont(const std::string &file);
    Glyph Get(char character);
};

Font::Font(const std::string &file)
{
    CreateFontTable(file, glyphs);
}

void Font::SetFont(const std::string &file)
{
    CreateFontTable(file, glyphs);
}

Glyph Font::Get(char character)
{
    return glyphs[character];
}