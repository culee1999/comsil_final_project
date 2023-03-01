#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup(); // 지뢰찾기 게임 시작 전 환경을 만들어주는 함수
		void update();
		void draw(); // 지뢰찾기 게임 실행한 결과를 그려주는 함수

		void keyPressed(int key); // 특정 버튼 눌렀을 때, 특정 함수 호출해주는 함수
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button); // 마우스 클릭했을 때의 위치를 반환하는 함수
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void dig(int x, int y); // 마우스 왼쪽 클릭했을 때, 클릭한 위치의 블록을 열어주는 함수
		void mine_draw(); // 특정 블록에 마우스 왼쪽 클릭했을 때, 블록을 오픈하고 블록의 상태를 그려주는 함수
		void flag_draw(); // 특정 블록에 마우스 오른쪽 클릭을 했을 때, 깃발 모양을 그려주는 함수
		void check(); // 게임이 클리어 되었는지 여부를 확인하는 함수
		void square(); // 지뢰찾기 게임 베이스로 정사각형을 설정하는 함수
		void heart(); // 지뢰찾기 게임 베이스로 하트 모양을 설정하는 함수
		void smile(); // 미로찾기 상단 중앙에 스마일 이모티콘 그리는 함수

		ofImage mine_pic; // 지뢰 그림을 저장할 변수
		ofImage life; // 목숨 그림을 저장할 변수
};
