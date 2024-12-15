// Code taken from @MightyPork at:
// https://stackoverflow.com/questions/4965335/how-to-print-binary-tree-diagram
// Has been rewritten to C++ here.

#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

class PrintableNode 
{
public:
	virtual ~PrintableNode() = default;

	virtual PrintableNode* getLeft() const = 0;

	virtual PrintableNode* getRight() const = 0;

	virtual std::wstring getText() const = 0;
};

static std::wstring getTreeDisplay(const PrintableNode* root) 
{
	std::wstring sb;
	std::vector<std::vector<std::wstring>> lines;
	std::vector<const PrintableNode*> level;
	std::vector<const PrintableNode*> next;

	level.push_back(root);
	int nn = 1;
	int widest = 0;

	// Level-order traversal to populate lines
	while (nn != 0) 
	{
		nn = 0;
		std::vector<std::wstring> line;
		for (const PrintableNode* n : level) 
		{
			if (n == nullptr) 
			{
				line.emplace_back(L"");
				next.emplace_back(nullptr);
				next.emplace_back(nullptr);
			}
			else 
			{
				std::wstring aa = n->getText();
				line.emplace_back(aa);
				if (static_cast<int>(aa.length()) > widest) 
				{
					widest = static_cast<int>(aa.length());
				}

				next.emplace_back(n->getLeft());
				next.emplace_back(n->getRight());

				if (n->getLeft() != nullptr)
					nn++;

				if (n->getRight() != nullptr)
					nn++;
			}
		}

		// Ensure widest is even
		if (widest % 2 == 1) widest++;

		lines.emplace_back(line);

		// Prepare for next level
		level = next;
		next.clear();
	}

	if (lines.empty()) 
	{
		return L"";
	}

	int perpiece = static_cast<int>((lines.back().size()) * (widest + 4));

	for (size_t i = 0; i < lines.size(); i++) 
	{
		const std::vector<std::wstring>& line = lines[i];
		int hpw = static_cast<int>(std::floor(perpiece / 2.0)) - 1;

		if (i > 0) 
		{
			for (size_t j = 0; j < line.size(); j++) 
			{
				wchar_t c = L' ';
				if (j % 2 == 1) 
				{
					if (!lines[i - 1][j / 2].empty()) 
					{
						if (!line[j].empty()) 
						{
							c = L'┴';
						}
						else 
						{
							c = L'┘';
						}
					}
					else 
					{
						if (j < line.size() && !line[j].empty()) c = L'└';
					}
				}

				sb += c;

				// Append spaces or connectors
				if (line[j].empty()) 
				{
					sb += std::wstring(perpiece - 1, L' ');
				}
				else 
				{
					for (int k = 0; k < hpw; k++)
						sb += (j % 2 == 0) ? L" " : L"─";

					sb += (j % 2 == 0) ? L"┌" : L"┐";

					for (int k = 0; k < hpw; k++)
						sb += (j % 2 == 0) ? L"─" : L" ";
				}
			}

			sb += L'\n';
		}

		// Print the node texts with appropriate spacing
		for (size_t j = 0; j < line.size(); j++) 
		{
			std::wstring f = line[j];
			if (f.empty()) f = L"";
			int gap1 = static_cast<int>(std::ceil(perpiece / 2.0 - f.length() / 2.0));
			int gap2 = static_cast<int>(std::floor(perpiece / 2.0 - f.length() / 2.0));

			sb += std::wstring(gap1, L' ');
			sb += f;
			sb += std::wstring(gap2, L' ');
		}

		sb += L'\n';

		perpiece /= 2;
	}

	return sb;
}

