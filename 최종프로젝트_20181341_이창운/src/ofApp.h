#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup(); // ����ã�� ���� ���� �� ȯ���� ������ִ� �Լ�
		void update();
		void draw(); // ����ã�� ���� ������ ����� �׷��ִ� �Լ�

		void keyPressed(int key); // Ư�� ��ư ������ ��, Ư�� �Լ� ȣ�����ִ� �Լ�
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button); // ���콺 Ŭ������ ���� ��ġ�� ��ȯ�ϴ� �Լ�
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void dig(int x, int y); // ���콺 ���� Ŭ������ ��, Ŭ���� ��ġ�� ����� �����ִ� �Լ�
		void mine_draw(); // Ư�� ��Ͽ� ���콺 ���� Ŭ������ ��, ����� �����ϰ� ����� ���¸� �׷��ִ� �Լ�
		void flag_draw(); // Ư�� ��Ͽ� ���콺 ������ Ŭ���� ���� ��, ��� ����� �׷��ִ� �Լ�
		void check(); // ������ Ŭ���� �Ǿ����� ���θ� Ȯ���ϴ� �Լ�
		void square(); // ����ã�� ���� ���̽��� ���簢���� �����ϴ� �Լ�
		void heart(); // ����ã�� ���� ���̽��� ��Ʈ ����� �����ϴ� �Լ�
		void smile(); // �̷�ã�� ��� �߾ӿ� ������ �̸�Ƽ�� �׸��� �Լ�

		ofImage mine_pic; // ���� �׸��� ������ ����
		ofImage life; // ��� �׸��� ������ ����
};
