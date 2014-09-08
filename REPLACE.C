#include <os2.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	extern APIRET APIENTRY DosReplaceModule(PSZ pszOld, PSZ pszNew, PSZ pszBack);
	int		i;
	
	if(argc == 1)
	{
		printf("Usage: Replace ModuleName [ModuleName ...]\n");
		printf("Note: ModuleName must be a fully qualified path.\n");
		return 0;
	}

	for(i=1; i<argc; i++)
		DosReplaceModule(argv[i], NULL, NULL);

	return 0;
}