#include "stdafx.h"
#include "AnimationClip.h"
#include "rapidcsv.h"

bool AnimationClip::loadFromFile(const std::string& filePath)
{
	rapidcsv::Document doc(filePath);
	id = doc.GetCell<std::string>(0, 0);//아이디값
	fps = doc.GetCell<int>(1, 0);	//실제 0,0
	loopType = (AnimationLoopTypes)doc.GetCell<int>(2, 0);

	frames.clear();
	for (int i = 4; i < doc.GetRowCount(); ++i) //행을 제외하고 
	{
		auto row = doc.GetRow<std::string>(i);
		if (row.size() < 5)
			continue;

		AnimationFrame frame(
			row[0], // texId, ex) "graphics/niko.png"
			sf::IntRect(
				std::stoi(row[1]), // left
				std::stoi(row[2]), // top
				std::stoi(row[3]), // width
				std::stoi(row[4])  // height
			)
	);
	frames.push_back(frame);
		/*frames.push_back(
			{ 
				row[0], 
				{ std::stoi(row[1]),
				std::stoi(row[2]),
				std::stoi(row[3]),
				std::stoi(row[4]) }
			});*/
	}

	return true;
}
