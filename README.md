# CROSSSING-GRAME-OOP-Project
A game where player's character's task is to cross the road safely without collision/crashing the obstacles

Class Vehicle: Gồm các class con là Cat, Car, Bus, Truck
•	Là các vật cản di chuyển trên màn hình
•	Có 4 loại vật cản tương ứng với các class con, và có hai cách di chuyển là từ trái sang phải hoặc ngược lại.
•	Tọa độ của “Vehicle” là y: tính từ vị trí cao nhất của vật cản, x sẽ tính là vị trí bên trái nhất với “Vehicle” di chuyển từ trái sang phải và là bên phải nhất với “Vehicle” di chuyển từ phải sang trái, từ đó tương ứng với từng cách vẽ “Vehicle” ra màn hình
Chi tiết:
Attribute: 
•	int x,y: tọa độ
•	int direction: hướng di chuyển
•	short type: loại Vehicle: (Car: 1, Cat: 2, Truck: 3, Bus: 4)
•	short length: chiều dài của Vehicle
•	short height: chiều cao của Vehicle
•	string picture[4]: chứa ký tự để vẽ Vehicle
Function:
•	void move(): hàm thay đổi tọa độ x của Vehicle (hàm di chuyển)
•	void draw(): hàm in Vehicle

----------------------------------------------------------------------------------------------------------------------
Class trafficLight: đèn tín hiệu
•	Đèn tín hiệu có hai trạng thái là xanh và đỏ tương ứng với hai trạng thái của Vehicle là di chuyển và dừng lại
Chi tiết:
Attribute: 
•	int y: tọa độ y theo chiều dọc (x được quy định sẵn)
•	bool isRed: cờ báo đèn hiệu *ở trạng thái đèn đỏ hay không
•	int order: số thứ tự (chạy từ 1-6)
*Function: 
•	void setRedOn(): bật đèn đỏ
•	void setGreenOn(): tắt đèn đỏ
•	bool isRedLight(): kiểm tra xem đèn đỏ hay không
•	void draw(): vẽ đèn

----------------------------------------------------------------------------------------------------------------------
Class lane:
•	Quản lý các “Vehicle” có cùng tọa độ y (cả game gồm 6 lane)
•	Mỗi lane có một đèn tín hiệu
Chi tiết:
Attribute:
•	int Level: level của game hiện tại
•	int order: số thứ tự của lane (chạy từ 1-6)
•	deque<Vehicle*> point: hàng đợi chứa các Vehicle trong cùng một lane
•	int direction: hướng đi của các Vehicle trong lane (mỗi lane chỉ có các loại vehicle đi cùng một hướng)
•	trafficLight light: đèn tín hiệu
•	int countTimeForRedLight: biến đếm thời gian, sau khoảng thời gian quy định sẽ đổi đèn tín hiệu
•	const int time[5]: thời gian qui định đèn tín hiệu sẽ đổi theo từng level
Function:
•	void updateLane(): cập nhật tọa độ các vehicle và trạng thái đèn tín hiệu
•	void drawVehicle(): vẽ Vehicle
•	void drawLight(): vẽ đèn tín hiệu
•	void returnEachVehicle(const int&): trả về từng vehicle trong lane (để hàm isImpact của class People kiểm tra xem có xảy ra đụng đồ giữa Vehicle và People)

----------------------------------------------------------------------------------------------------------------------
Class CPEOPLE: Nhân vật mà người chơi điều khiển**
•	Nhân vật có hai trạng thái là sống và chết.
•	Trạng thái mặc định là “sống” nhưng khi di chuyển trúng “Vehicle” sẽ thay đổi sang trạng thái “chết”
Chi tiết:
Attribute:
•	int mX, mY: tọa độ x,y
•	bool mState: trạng thái sống/chết
•	char c: biến tạm để nhận phím từ bàn phím và di chuyển
Function:
•	bool isFinish(): kiểm tra xem người chơi qua màn không
•	bool isImpact(Vehicle* ): kiểm tra có xảy ra đụng độ
•	bool isDead(): kiểm tra trạng thái people
•	void move(): hàm di chuyển
•	void draw(): hàm vẽ người

----------------------------------------------------------------------------------------------------------------------
Class Game: 
•	Quản lý các class chính của game (lane và people)
•	Quản lý cách trò chơi vận hành và các chức năng của game
•	Chứa thông tin người chơi (tên và level)
Chi tiết:
Attribute: 
•	string player: tên người chơi (mặc định là unknown)
•	int level: level game hiện tại
•	int speed: thời gian chờ màn hình (tốc độ di chuyển nhanh hay chậm của Vehicle)
•	CPEOPLE people: nhân vật người chơi
•	vector<lane*> list: dãy các lane của game (lane quản lý Vehicle, Game quản lý lane)
•	bool IS_WINING: biến kiểm tra xem có win game
•	bool LOSE_BOARD: biến kiểm tra xem hiệu ứng thua game đã chạy xong chưa
•	bool IS_RUNNING: cờ để hàm subThread chạy vòng lặp
Funtion:
•	void gameRepair(): khởi tạo các giá trị cho các thuộc tính  của class game
•	void updateLane(): cập nhật trạng thái lane (lane cập nhật trạng thái Vehicle, trafficLight)
•	void updatePeople(): cập nhật trạng thái CPEOPLE 
•	void drawLane(): vẽ lane
•	void drawLight(): vẽ đèn
•	bool isImpact(): kiểm tra xem có đụng độ xảy ra
•	void deadAnimation(): chạy hiệu ứng thua game
•	void gamePlay(): hàm chính chạy game
•	void pause(): chức năng tạm dừng trò chơi 
•	void resume(): chức năng tiếp tục trò chơi
•	void newGame(): chức năng quay về menu điều hướng
•	void deleteSource(): giải phóng bộ nhớ

----------------------------------------------------------------------------------------------------------------------
**Hai hàm vận hành chính:**
•	subThread(): thread để vẽ animation lên console
•	Game::gamePlay(): thread bắt phím nhập từ bàn phím và quản lý subThread cũng như các chức năng của game.

----------------------------------------------------------------------------------------------------------------------
**Các hàm chức năng:**
•	menu(): quản lý hàm loadGame() và bật tắt nhạc nền
•	void drawWin(): hiệu ứng chiến thắng
•	pause(), resume(), save() tương ứng với từng chức năng 
