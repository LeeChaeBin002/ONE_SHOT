#include "stdafx.h"
#include "AnimationClip.h"
#include "rapidcsv.h"
#include <filesystem>

bool AnimationClip::loadFromFile(const std::string& filePath)
{
	std::cout << "[시도 중] 파일 열기: " << filePath << std::endl;
	std::cout << "[작업 디렉터리] " << std::filesystem::current_path() << std::endl;

	try
	{
		// 이 줄에서 예외가 발생하므로, try 안에 있어야 함
		rapidcsv::Document doc(filePath);

		std::cout << "CSV 로드 성공!" << std::endl;
		id = doc.GetCell<std::string>(0, 1);
		fps = doc.GetCell<int>(1, 1);
		loopType = (AnimationLoopTypes)doc.GetCell<int>(2, 1);

		frames.clear();

		for (int i = 2; i < doc.GetRowCount(); ++i) // 프레임 정보 시작
		{
			try {

			
			auto row = doc.GetRow<std::string>(i);

			if (row.size() < 6) {
				std::cerr << "[스킵] 줄 " << i << "의 데이터가 부족합니다: " << row.size() << "개 항목" << std::endl;
				continue;
			}

	
				std::string texId = row[0];
				int left = std::stoi(row[1]);
				int top = std::stoi(row[2]);
				int width = std::stoi(row[3]);
				int height = std::stoi(row[4]);

				// 필요시 FlipX는 row[5]에서 처리

				AnimationFrame frame(texId, sf::IntRect(left, top, width, height));
				frames.push_back(frame);
			}
			catch (const std::exception& e) {
				std::cerr << "[프레임 파싱 실패] 줄 " << i << ": " << e.what() << std::endl;
				continue;
			}
		}

		return true;
	}
	catch (const std::exception& e)
	{
		std::cerr << "[예외 발생] " << e.what() << std::endl;
		std::cerr << "경로: " << filePath << std::endl;
		std::cerr << "작업 디렉터리: " << std::filesystem::current_path() << std::endl;
		return false;
	}
}