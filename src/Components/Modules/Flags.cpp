#include "STDInclude.hpp"

namespace Components
{
	std::vector<std::string> Flags::EnabledFlags;

	bool Flags::HasFlag(std::string flag)
	{
		Flags::ParseFlags();

		for (auto entry : Flags::EnabledFlags)
		{
			if (Utils::StrToLower(entry) == Utils::StrToLower(flag))
			{
				return true;
			}
		}

		return false;
	}

	void Flags::ParseFlags()
	{
		static bool flagsParsed = false;
		if (flagsParsed) return;
		flagsParsed = true;

		int numArgs;
		LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &numArgs);

		if (argv)
		{
			for (int i = 0; i < numArgs; ++i)
			{
				std::wstring wFlag(argv[i]);
				if (wFlag[0] == L'-')
				{
					Flags::EnabledFlags.push_back(std::string(++wFlag.begin(), wFlag.end()));
				}
			}

			LocalFree(argv);
		}
	}

	Flags::Flags()
	{
		Flags::ParseFlags();
	}

	Flags::~Flags()
	{
		Flags::EnabledFlags.clear();
	}
}
