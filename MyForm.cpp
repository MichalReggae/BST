#include "MyForm.h"
#include <fstream>
#include <iostream>
#include "des.h"


using namespace std;
using namespace System;
using namespace System::Windows::Forms;
[STAThreadAttribute]

void main() {	

	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	DESAPP::MyForm frm;
	Application::Run(% frm);

}
