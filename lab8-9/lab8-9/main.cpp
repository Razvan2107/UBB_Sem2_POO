#include "console.h"
#include "service.h"
#include "repo.h"
#include "repoLab.h"
#include "validator.h"

void aduaga_la_misto(ATService& srv)
{
	srv.addAT("d", "f", "if", 500);
	srv.addAT("b", "g", "ie", 200);
	srv.addAT("a", "h", "in", 400);
	srv.addAT("c", "e", "il", 300);
}

void TestAll()
{
	TestRepo();
	TestService();
	TestValidator();
}

int main()
{
	TestAll();
	//ATRepoLab rep(0.5);
	ATRepoFile rep{ "fisier.txt" };
	ATValidator val;
	ATService srv{rep,val};
	//aduaga_la_misto(srv);
	UI ui{ srv };
	ui.start();
}