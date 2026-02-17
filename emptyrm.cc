#include <filesystem>
#include <system_error>
#include <print>

bool emptyrm(std::filesystem::path p)
{
	std::error_code err;
	std::filesystem::directory_iterator iter(p, err);
	std::size_t count = 0;

	if (err)
	{
		std::println("{}: {}", err.value(), err.message());
		return false;
	}

	for (const auto &entry : iter)
	{
		++count;

		if (entry.is_directory())
		{
			if (emptyrm(entry))
				--count;
		}
	}

	if (count == 0)
		std::filesystem::remove(p, err);

	if (err)
		std::println("{}: {}", err.value(), err.message());

	return count == 0 && !err;
}

int wmain(int argc, wchar_t *argv[])
{
	for (int i = 1; i < argc; ++i)
		emptyrm(argv[i]);
}