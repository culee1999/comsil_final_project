#include "ofApp.h"

int diagram[10][10]; // 정사각형, 하트 모양 저장할 배열
int play_table[10][10]; // 가려진 경우 = 0, 클릭으로 오픈된 경우 = 1, 깃발 세워진 경우 = 2
int Mine_count[10][10]; // 근처에 지뢰 몇 갠지 나타내는 배열(ex 1이면 근처에 지뢰 1개), 9면 지뢰를 나타냄
int nx = 10, ny = 10; // 지뢰 찾기 게임 도형(정사각형, 하트)의 크기를 저장하는 변수
int gameplay = 0; // 게임 플레이 중 여부를 저장하는 변수
int gameover = 0; // 게임 오버 여부를 저장하는 변수
int nBomb = 10; // 지뢰 개수 저장하는 변수
int clear = 0; // 게임 클리어 여부를 저장하는 변수
int bomb_flag; // 숨겨진 블록+깃발 개수 저장하는 변수
int x_mine, y_mine; // 마우스의 x좌표와 y좌표를 저장하는 변수
int hp; // 목숨의 개수를 저장하는 변수
int figure = 1; // 지뢰 찾기 배경 모양 선택하는 변수

//--------------------------------------------------------------
void ofApp::setup(){ // 지뢰찾기 게임 시작 전 환경을 만들어주는 함수
	
	if (figure == 1) {
		square(); // 지뢰찾기 게임 배경을 정사각형으로 설정
		ofBackground(80); // 배경 색깔 - 회색
	}
	if (figure == 2) {
		heart(); // 지뢰찾기 게임 배경 하트로 설정
		ofBackground(255,153,204); // 배경 색깔 - 핑크색
	}
	gameplay = 1; // 게임 클리어 여부 나타내는 변수에 1 설정
	gameover = 0; // 게임 오버 여부 나타내는 변수에 0 설정
	clear = 0; // 클리어 여부 나타내는 변수에 0 설정
	hp = 3; // 목숨 나타내는 변수를 3으로 설정
	ofSetWindowTitle("MineSweeper"); // 프로그램 이름을 MineSweeper로 나타나게 설정
	ofSetWindowShape(1024, 768); // 윈도우 크기를 1024 * 768 로 맞추기
	ofSetBackgroundAuto(false); // 그려진 것이 사라지지 않게 하기 위한 코드
	srand((unsigned int)time(NULL)); // 랜덤한 경우를 만들기 위해 호출
	mine_pic.load("mine.png"); // 지뢰 이미지를 mine.png 파일에서 가져오기
	life.load("heart.png"); // 목숨 이미지를 heart.png 파일에서 가져오기

	for (int y = 0; y < ny; y++)
		for (int x = 0; x < nx; x++) { // 10*10 크기의 2차원 배열 전체를 반복
			play_table[y][x] = 0; // play_table 값 0으로 초기화
			Mine_count[y][x] = 0; // Mine_count 값 0으로 초기화
		}

	for (int i = 0; i < nBomb; i++) { // 지뢰 설치하기
		int x, y;
		x = rand() % nx; // 랜덤한 x 좌표
		y = rand() % ny; // 랜덤한 y 좌표
		while (Mine_count[y][x] != 0 || diagram[y][x] != 1) { // 랜덤한 위치의 x좌표와 y좌표 값이 diagram 값이 1이면서(=정사각형이나 하트 모양이 그려진 부분), 지뢰가 아닌 부분이
															  // 나올때까지 while 문 반복
			x = rand() % nx;
			y = rand() % ny;
		}
		Mine_count[y][x] = 9; // 지뢰 아니면서 diagram[y][x] 값이 1인 경우, 지뢰 설치
	}

	for (int y = 0; y < ny; y++)
		for (int x = 0; x < nx; x++) // 10*10 크기의 2차원 배열 전체를 반복
			if (Mine_count[y][x] == 0) { // 지뢰 아닌 경우
				int count = 0; // 근처 지뢰 개수 세서 저장할 변수 count에 0 할당
				for (int k = y - 1; k <= y + 1; k++) // y좌표 기준 주변에 해당하는 위쪽~아래쪽
					for (int l = x - 1; l <= x + 1; l++) // x좌표 기준 주변에 해당하는 왼쪽~오른쪽
						if (l >= 0 && l < nx && k >= 0 && k < ny && Mine_count[k][l] == 9) // 전체 게임 내에 있으면서, 지뢰인 경우
							count++; // count 값 1 증가
				Mine_count[y][x] = count; // Mine_count에, 주변 지뢰 개수 센 count 값 할당
			}
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){ // 지뢰찾기 게임 실행한 결과를 그려주는 함수
	smile(); // 지뢰찾기 위쪽 스마일 이모티콘 그리기

	ofSetColor(255); // 흰색
	ofDrawRectangle(50, 10, 100, 30); // 스마일 이모티콘 왼쪽에 직사각형 그리기
	for (int i = 0; i < hp; i++)
		life.draw(60 + i * 30, 20, 20, 10); // 직사각형 안쪽에, 목숨의 개수만큼 life 라는 이미지 파일 그려주기

	if (gameover == 1) { // 게임 오버 된 경우
		ofSetColor(102, 204, 255); // 하늘색
		ofDrawRectangle(200, 200, 200, 200); // 정사각형 그리기
		ofSetColor(0); // 검은색
		ofDrawBitmapString("Game Over!!", 250, 300); // 정사각형 안에 Game Over!! 출력하기
		ofDrawBitmapString("Retry?   Press R", 230, 330); // 정사각형 안에 재시도 출력하기
		return;
	}
	if (clear == 1){ // 게임 클리어 한 경우
		ofSetColor(102, 204, 255); // 하늘색
		ofDrawRectangle(200, 200, 200, 200); // 정사각형 그리기
		ofSetColor(0); // 검은색
		ofDrawBitmapString("Clear!!", 250, 300); // 정사각형 안에 Clear!! 출력하기
		ofDrawBitmapString("Retry?   Press R", 230, 330); // 정사각형 안에 재시도 출력하기
		return;
	}

	ofNoFill();
	ofSetColor(0); // 검은색
	for (int i = 0; i < ny; i++)
		for (int j = 0; j < nx; j++) {
			if (diagram[i][j] == 1) // diagram이라는 2차원 배열 값이 1인 경우(=하트나 정사각형에 해당하는 부분만 값이 1)
				ofDrawRectangle(50 * j + 50, 50 * i + 50, 50, 50); // 정사각형 그려주기
		}
	ofFill();

	ofSetColor(255); // 흰색
	ofDrawRectangle(650, 400, 100, 100); // 키설정 적을 정사각형 그리기
	ofSetColor(0); // 검은색
	ofDrawBitmapString("s : square", 660, 420);
	ofDrawBitmapString("h : heart", 660, 440);
	ofDrawBitmapString("r : reset", 660, 460);
	ofDrawBitmapString("a : answer", 660, 480); // '키 : 설명' 형태로 설명 작성

	if (gameplay == 1) { // 게임 플레이 중인 경우
		if (ofGetMousePressed(OF_MOUSE_BUTTON_LEFT)) { // 마우스 왼쪽 클릭한 경우
			dig(x_mine / 50 - 1, y_mine / 50 - 1); // 마우스 왼쪽 클릭했을 때의 좌표를 수정해서, dig 함수 실행
			mine_draw(); // dig 함수 실행으로 바뀐 Mine_count 배열의 값에 따라 그려주는 함수 실행
			Sleep(100); // 100ms 딜레이 시키기
		}
		if (ofGetMousePressed(OF_MOUSE_BUTTON_RIGHT)) {// 마우스 오른쪽 클릭한 경우
			flag_draw(); // 깃발 그려주거나 지우기
			Sleep(100); // 100ms 딜레이 시키기(마우스로 1번 클릭했는데, 컴퓨터가 3~4회 클릭한 걸로 인식하는 것을 방지하기 위함)
		}
	}

	check(); // 게임 클리어 여부 확인하는 함수 호출
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){ // 특정 버튼 눌렀을 때, 특정 함수 호출해주는 함수
	if (key == 'r' || key == 'R') // 리셋 + 새로 시작
		setup();

	if (key == 'a' || key == 'A') { // 정답
		printf("\n");
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++)
				printf("%d ", Mine_count[i][j]);
			printf("\n");
		}
	}

	if (key == 's' || key == 'S') { // 지뢰 찾기 배경 정사각형으로 설정
		figure = 1; // figure 변수에 1 할당(= 배경이 정사각형)
		setup();
	}

	if (key == 'h' || key == 'H') { // 지뢰 찾기 배경 하트로 설정
		figure = 2; // figure 변수에 1 할당(= 배경이 하트)
		setup();
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){ // 마우스 클릭했을 때의 위치를 반환하는 함수
	x_mine = mouseX; // 마우스 클릭 기준 x좌표를 x_mine 이라는 변수에 저장
	y_mine = mouseY; // 마우스 클릭 기준 y좌표를 y_mine 이라는 변수에 저장
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::dig(int x, int y) { // 마우스 왼쪽 클릭했을 때, 클릭한 위치의 블록을 열어주는 함수
	if (x >= 0 && x < nx && y >= 0 && y < ny && play_table[y][x] == 0 && diagram[y][x] == 1) { // 마우스 좌표가 전체 블록 내부에 있으면서, play_table 값이 0(=가려져 있던 경우)이면서
																							   // diagram 값이 1인 경우(=정사각형이나 하트 모양이 그려진 부분)에만 if문 실행
		play_table[y][x] = 1; // play_table 값을 1로 수정(=해당 블록이 오픈된 경우)
		if (Mine_count[y][x] == 0) { // 추가로 클릭한 블록 주변에, 지뢰가 아예 없는(=Mine_count 값이 0) 블록이 있으면, 추가로 dig 함수 실행
			dig(x - 1, y - 1); // 클릭 블록 기준으로 좌측 상단 dig 함수 실행
			dig(x - 1, y); // 클릭 블록 기준으로 좌측 dig 함수 실행
			dig(x - 1, y + 1); // 클릭 블록 기준으로 좌측 하단 dig 함수 실행
			dig(x, y - 1); // 클릭 블록 기준으로 상단 dig 함수 실행
			dig(x, y + 1); // 클릭 블록 기준으로 하단 dig 함수 실행
			dig(x + 1, y - 1); // 클릭 블록 기준으로 우측 상단 dig 함수 실행
			dig(x + 1, y); // 클릭 블록 기준으로 우측 dig 함수 실행
			dig(x + 1, y + 1); // 클릭 블록 기준으로 우측 하단 dig 함수 실행
		}
	}
}

void ofApp::mine_draw() { // 특정 블록에 마우스 왼쪽 클릭했을 때, 블록을 오픈하고 블록의 상태를 그려주는 함수
	if (x_mine >= 50 && x_mine < 550 && y_mine >= 50 && y_mine < 550) { // 마우스 좌표가, 전체 블록 안쪽에 위치한 경우에만 함수가 실행되도록 설정
		int x = x_mine / 50 - 1; // 마우스 위치의 값과 2차원 배열들의 값을 비교하기 위해, 마우스 x좌표 값을 수정해서, x라는 int 변수에 할당
		int y = y_mine / 50 - 1; // 마우스 위치의 값과 2차원 배열들의 값을 비교하기 위해, 마우스 y좌표 값을 수정해서, y라는 int 변수에 할당

		if (diagram[y][x] == 1) { // diagram이라는 2차원 배열 값이 1인 경우(=정사각형이나 하트 모양이 그려진 부분)에만 if문 실행
			for (int i = 0; i < ny; i++)
				for (int j = 0; j < nx; j++) { // 10*10 크기의 Mine_count 배열의 전체를 살펴본다
					ofSetColor(255); // 흰색
					if (play_table[i][j] == 1) { // play_table 값이 1인 경우(=블록이 오픈 된 경우)
						if (Mine_count[i][j] == 0) // Mine_count 배열의 값이 0인 경우(=주변 8칸 블록에 지뢰가 없음)
							ofDrawRectangle(j * 50 + 50, i * 50 + 50, 50, 50); // 해당하는 블록에 정사각형 그리기

						if (Mine_count[i][j] == 1) { // Mine_count 배열의 값이 1인 경우(=주변 8칸 블록에 지뢰가 1개)
							ofDrawRectangle(j * 50 + 50, i * 50 + 50, 50, 50); // 해당하는 블록에 정사각형 그리기
							ofSetColor(0); // 검은색
							ofDrawBitmapString("1", j * 50 + 75, i * 50 + 75); // 블록 가운데에 1 그려주기
						}

						if (Mine_count[i][j] == 2) { // Mine_count 배열의 값이 2인 경우(=주변 8칸 블록에 지뢰가 2개)
							ofDrawRectangle(j * 50 + 50, i * 50 + 50, 50, 50); // 해당하는 블록에 정사각형 그리기
							ofSetColor(0); // 검은색
							ofDrawBitmapString("2", j * 50 + 75, i * 50 + 75); // 블록 가운데에 2 그려주기
						}

						if (Mine_count[i][j] == 3) { // Mine_count 배열의 값이 3인 경우(=주변 8칸 블록에 지뢰가 3개)
							ofDrawRectangle(j * 50 + 50, i * 50 + 50, 50, 50); // 해당하는 블록에 정사각형 그리기
							ofSetColor(0); // 검은색
							ofDrawBitmapString("3", j * 50 + 75, i * 50 + 75); // 블록 가운데에 3 그려주기
						}

						if (Mine_count[i][j] == 4) { // Mine_count 배열의 값이 4인 경우(=주변 8칸 블록에 지뢰가 4개)
							ofDrawRectangle(j * 50 + 50, i * 50 + 50, 50, 50); // 해당하는 블록에 정사각형 그리기
							ofSetColor(0); // 검은색
							ofDrawBitmapString("4", j * 50 + 75, i * 50 + 75); // 블록 가운데에 4 그려주기
						}

						if (Mine_count[i][j] == 5) { // Mine_count 배열의 값이 5인 경우(=주변 8칸 블록에 지뢰가 5개)
							ofDrawRectangle(j * 50 + 50, i * 50 + 50, 50, 50); // 해당하는 블록에 정사각형 그리기
							ofSetColor(0); // 검은색
							ofDrawBitmapString("5", j * 50 + 75, i * 50 + 75); // 블록 가운데에 5 그려주기
						}

						if (Mine_count[i][j] == 6) { // Mine_count 배열의 값이 6인 경우(=주변 8칸 블록에 지뢰가 6개)
							ofDrawRectangle(j * 50 + 50, i * 50 + 50, 50, 50); // 해당하는 블록에 정사각형 그리기
							ofSetColor(0); // 검은색
							ofDrawBitmapString("6", j * 50 + 75, i * 50 + 75); // 블록 가운데에 6 그려주기
						}

						if (Mine_count[i][j] == 7) { // Mine_count 배열의 값이 7인 경우(=주변 8칸 블록에 지뢰가 7개)
							ofDrawRectangle(j * 50 + 50, i * 50 + 50, 50, 50); // 해당하는 블록에 정사각형 그리기
							ofSetColor(0); // 검은색
							ofDrawBitmapString("7", j * 50 + 75, i * 50 + 75); // 블록 가운데에 7 그려주기
						}

						if (Mine_count[i][j] == 8) { // Mine_count 배열의 값이 8인 경우(=주변 8칸 블록에 지뢰가 8개)
							ofDrawRectangle(j * 50 + 50, i * 50 + 50, 50, 50); // 해당하는 블록에 정사각형 그리기
							ofSetColor(0); // 검은색
							ofDrawBitmapString("8", j * 50 + 75, i * 50 + 75); // 블록 가운데에 8 그려주기
						}

						if (Mine_count[i][j] == 9) { // Mine_count 배열의 값이 9인 경우(=해당 블록이 지뢰)
							hp--; // 목숨 개수 1 감소
							ofDrawRectangle(j * 50 + 50, i * 50 + 50, 50, 50); // 해당하는 블록에 정사각형 그리기
							mine_pic.draw(j * 50 + 50, i * 50 + 50, 50, 50); // 지뢰 이미지 가져와서 그려주기
							play_table[i][j] = 4; // play_table 값을 4로 수정(=폭탄 발견했고 오픈한 경우)
							if (hp == 0) { // 목숨이 0이 된 경우
								gameover = 1; // 게임 오버 여부 나타내는 변수 1로 수정
								gameplay = 0; // 게임 플레이 중 나타내는 변수 0으로 수정
							}
						}
					}
				}
		}
	}
}

void ofApp::flag_draw() { // 특정 블록에 마우스 오른쪽 클릭을 했을 때, 깃발 모양을 그려주는 함수
	if (x_mine >= 50 && x_mine < 550 && y_mine >= 50 && y_mine < 550) { // 마우스 좌표가, 전체 블록 안쪽에 위치한 경우에만 함수가 실행되도록 설정
		int x = x_mine / 50 - 1; // 마우스 위치의 값과 2차원 배열들의 값을 비교하기 위해, 마우스 x좌표 값을 수정해서, x라는 int 변수에 할당
		int y = y_mine / 50 - 1; // 마우스 위치의 값과 2차원 배열들의 값을 비교하기 위해, 마우스 y좌표 값을 수정해서, y라는 int 변수에 할당

		if (diagram[y][x] == 1) { // diagram이라는 2차원 배열 값이 1인 경우(=정사각형이나 하트 모양이 그려진 부분)에만 if문 실행
			if (play_table[y][x] == 0) { // play_table 값이 0인 경우(=블록이 가려진 상태)
				play_table[y][x] = 2; // play_table 값을 2로 수정(=깃발 세워진 경우)
				ofSetColor(255, 0, 0); // 빨간색
				ofDrawTriangle(x * 50 + 65, y * 50 + 65, x * 50 + 75, y * 50 + 60, x * 50 + 75, y * 50 + 70); // 깃발 윗부분 삼각형 그리기
				ofSetColor(0); // 검은색
				ofDrawLine(x * 50 + 75, y * 50 + 70, x * 50 + 75, y * 50 + 80); // 깃발대 부분 그리기
				ofDrawRectangle(x * 50 + 65, y * 50 + 80, 20, 5); // 깃발 바닥 그리기
				return; // 함수 종료
			}
			else if (play_table[y][x] == 2) { // play_table 값이 0이 아니면서, 2인 경우(=깃발 세워진 경우) if문 실행
				play_table[y][x] = 0; //play_table 값을 0으로 수정(=블록이 가려진 상태)
				ofSetColor(80); // 회색
				ofDrawRectangle(x * 50 + 50, y * 50 + 50, 50, 50); // 깃발 부분 지우기 위해서, 정사각형으로 덮어 씌우기
				return; // 함수 종료
			}
		}
	}
}

void ofApp::check() { // 게임이 클리어 되었는지 여부를 확인하는 함수
	int bomb_flag = 0; // 지뢰와 깃발 개수를 세서 저장하는 변수
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			if (play_table[i][j] != 1 && diagram[i][j] == 1)
				bomb_flag++; // 10*10 크기의 2차원 배열인 play_table과 diagram 배열의 전체 값을 확인해서, play_table 값이 1이 아니면서(=숨겨져있는 경우거나 flag가 설치된 경우)
							 // diagram 배열 값이 1인 경우(=정사각형이나 하트 모양에 해당하는 부분) bomb_flag 변수 값을 1씩 증가시킨다. 이렇게하면, 지뢰+깃발 개수를 확인할 수 있다.
	if (bomb_flag == nBomb) { // 지뢰 개수와 bomb_flag(지뢰+깃발 개수)가 일치한 경우
		clear = 1; // 클리어 여부 확인하는 변수 1로 수정
		gameplay = 0; // 게임 플레이 중을 나타내는 변수 0으로 수정
	}
}

void ofApp::square() { // 지뢰찾기 게임 베이스로 정사각형을 설정하는 함수
	// 10 * 10 크기의 diagram이라는 2차원 배열에, 정사각형에 해당하는 부분만 1을 할당함
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			diagram[i][j] = 0; // 기존의 diagram 배열의 모든 값을 0으로 초기화

	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			diagram[i][j] = 1; // diagram 배열에서 정사각형에 해당하는 부분에 1 할당
}

void ofApp::heart() { // 지뢰찾기 게임 베이스로 하트 모양을 설정하는 함수
	// 10 * 10 크기의 diagram이라는 2차원 배열에, 하트 모양에 해당하는 부분만 1을 할당함

	ofSetColor(80); // 회색
	ofDrawRectangle(50, 50, 500, 500); // 기존의 정사각형 배경을 지우기 위해, 너비와 높이 500의 정사각형을 그리기

	for (int i = 0; i < ny; i++)
		for (int j = 0; j < nx; j++)
			diagram[i][j] = 0; // 기존의 diagram 배열의 모든 값을 0으로 초기화

	diagram[2][2] = 1;
	diagram[2][7] = 1;
	diagram[3][1] = 1;
	diagram[3][2] = 1;
	diagram[3][3] = 1;
	diagram[3][6] = 1;
	diagram[3][7] = 1;
	diagram[3][8] = 1;
	for (int i = 0; i < 10; i++)
		diagram[4][i] = 1;
	for (int i = 1; i < 9; i++)
		diagram[5][i] = 1;
	for (int i = 2; i < 8; i++)
		diagram[6][i] = 1;
	for (int i = 3; i < 7; i++)
		diagram[7][i] = 1;
	diagram[8][4] = 1;
	diagram[8][5] = 1; // diagram 배열에서 하트에 해당하는 부분에 1 할당
}

void ofApp::smile() { // 미로찾기 상단 중앙에 스마일 이모티콘 그리는 함수
	ofSetColor(0); // 검은색
	ofDrawRectangle(285, 10, 30, 30); // 스마일 이모티콘 위치할 상자 그리기
	ofSetColor(255, 255, 0); //노란색
	ofDrawCircle(300, 25, 13); // 스마일 이모티콘의 베이스인 원 그리기
	ofSetColor(0); // 검은색
	ofDrawBitmapString("^^", 293, 25); // 스마일 이모티콘의 눈 그리기
	ofDrawBitmapString("v", 297, 30); // 스마일 이모티콘의 입 그리기

	if (gameover == 1) { // 게임 오버되었을 때, 스마일 이모티콘 수정하는 과정
		ofSetColor(255, 255, 0); // 노란색
		ofDrawCircle(300, 25, 13); // 기존의 이모티콘에 덧칠하기 위해서, 노란색 원을 다시 그리기
		ofSetColor(0); // 검은색
		ofDrawBitmapString("xx", 293, 25); // 게임 오버 되었을 때의 눈 그리기
		ofDrawBitmapString("^", 297, 35); // 게임 오버 되었을 때의 입 그리기
	}

	if (clear == 1) { // 게임 클리어했을 때, 스마일 이모티콘 수정하는 과정
		ofSetColor(0); // 검은색
		ofDrawTriangle(293, 16, 301, 16, 297, 22); // 기존 스마일 이모티콘의 눈 위치에 역 삼각형 모양 그리기(선글라스 한쪽)
		ofDrawTriangle(301, 16, 309, 16, 305, 22); // 기존 스마일 이모티콘의 눈 위치에 역 삼각형 모양 그리기(선글라스 한쪽)
	}
}
