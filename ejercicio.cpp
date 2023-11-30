#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct ColorConsole
{
    static constexpr auto fg_blue = "\033[34m";
    static constexpr auto bg_white = "\033[47m";
};

struct ConsoleBox
{
    void new_text() {/*...*/}
    void set_text(const string &text) { cout << text << endl; }
};

ConsoleBox *consoleBox = new ConsoleBox; // Suponemos que ya está inicializado

void load_script(const char* filename, bool show_script = false)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "Error al abrir el archivo: " << filename << endl;
        return;
    }

    try
    {
        string script;
        string line;

        while (getline(file, line))
        {
            script += line + "\n";
        }

        file.close();

        if (show_script)
        {
            cout << ColorConsole::fg_blue << ColorConsole::bg_white;
            cout << script << endl;
        }

        consoleBox->new_text();
        consoleBox->set_text(script);
    }
    catch (const exception &e)
    {
        cerr << "Error durante la lectura del archivo: " << e.what() << endl;
        file.close();
    }
}

void load_script()
{
    string filename;

    cout << "Ingrese el nombre del archivo: ";
    cin >> filename;

    load_script(filename.c_str(), true);
}

int main()
{
    load_script(); // Solicitará al usuario el nombre del archivo y mostrará su contenido
    // También puedes llamar load_script("nombre_del_archivo.txt", true); directamente con un nombre de archivo específico

    return 0;
}
