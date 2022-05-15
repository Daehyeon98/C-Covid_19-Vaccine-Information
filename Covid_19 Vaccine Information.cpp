#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <random>

using namespace std;

class CVI {
    string state;
    string solution;
public:
    CVI(string n = 0, string c = 0) {
        state = n;
        solution = c;
    }
    string getState() {
        return state;
    }
    string getSolution() {
        return solution;
    }
};

const vector<string> SYMPTOM_CHECKLIST = {
    "미열이 있으신가요?",
    "기침을 자주 하시나요?",
    "호흡곤란이 있으신가요?",
    "오한이 있으신가요?",
    "근육통이 있으신가요?",
    "두통이 있으신가요?",
    "인후통이 있으신가요?",
    "후각 또는 미각 소실이 있으신가요?",
    "식욕이 감소하셨나요?",
    "결막염이 생기셨나요?",
};

const map<vector<int>, string> SYMPTOM_DIAGNOSE = {
    {{0}, "  진통제 섭취, 충분한 수분 섭취"},
    {{1}, "  따뜻한 물 자주 마시기, 흡연자일시 금연"},
    {{2}, "  의료기간 방문"},
    {{3}, "  신체 온도를 보호하기 위해 옷 입기"},
    {{4}, "  진통제 섭취, 충분한 휴식"},
    {{5}, "  진통제 섭취 충분한 휴식"},
    {{6}, "  탈수 증상이 일어나지 않도록 충분한 수분을 섭취"},
    {{7}, "  의료기간 방문"},
    {{8}, "  시간마다 식사 거르지 않기, 충분한 휴식"},
    {{9}, "  의료기간 방문"},
};

bool is_number(const string& s) {
    string::const_iterator it = s.begin();
    while (it != s.end() && isdigit(*it)) ++it;
    return !s.empty() && it == s.end(); //전달 받은 문자열이 숫자로 구성된 문자열인지 검사하는 함수로 수정
}

int int_input() {
    string line;

    do {
        if (line != "") {
            cout << "숫자만 입력해주세요 : ";
        }
        cin >> line;
    } while (!is_number(line));

    return atoi(line.c_str());
} // 숫자가 아닌 다른 문자를 입력하면 숫자를 입력하면 숫자를 입력할 때까지 재입력 요구 수정

vector<int> input_symptoms() {
    vector<int> symptoms;
    for (int i = 0; i < SYMPTOM_CHECKLIST.size(); i++) { //확인할 증상을 나열해놓은 벡터 변수
        cout << (i + 1) << ". " << SYMPTOM_CHECKLIST[i] << " (o/x)" << endl;

        string input;
        do {
            cout << ">> ";
            cin >> input;
            transform(input.begin(), input.end(), input.begin(), ::tolower);
        } while (input != "o" && input != "x");

        if (input == "o") {
            symptoms.push_back(i);
        }
    }
    return symptoms;
}

map<vector<int>, string> diagnose_symptoms(const vector<int>& symptoms) {
    map<vector<int>, string> result;

    for (const auto& it : SYMPTOM_DIAGNOSE) { //증상 벡터와 진단 결과를 매핑해놓은 변수
        if (includes(symptoms.begin(), symptoms.end(), it.first.begin(), it.first.end())) {
            result[it.first] = it.second;
        }
    }

    return result;
}

void symptoms() {
    // 사용자로부터 증상 입력
    vector<int> symptoms = input_symptoms();
    if (symptoms.empty()) {
        cout << "\n";
        cout << "증상이 없습니다!\n" << endl;
        return;
    }

    // 입력받은 증상 번호 출력
    cout << "\n";
    cout << "  " << symptoms.size() << "개의 증상이 있습니다.\n" << endl;
    cout << "=> ";
    for (int i = 0; i < symptoms.size(); i++) {
        if (i > 0) {
            cout << ", ";
        }
        cout << (symptoms[i] + 1);
    }
    cout << endl;

    map<vector<int>, string> diagnose_result = diagnose_symptoms(symptoms);
    if (diagnose_result.empty()) {
        cout << "진단 결과가 없습니다!\n" << endl;
        return;
    }

    cout << "  " << diagnose_result.size() << "개의 진단 결과가 있습니다.\n" << endl;
    cout << "□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n";
    cout << "\n";
    int index = 1;
    for (const auto& it : diagnose_result) {
        cout << it.second << " (";
        for (int i = 0; i < it.first.size(); i++) {
            if (i > 0) {
                cout << ", ";
            }
            cout << (it.first[i] + 1);
        }
        cout << ")" << endl;
    }
} // 2번기능 구현방법 변경(보기 중 자신의 증상 입력받기 -> 증상 체크 형식으로 변경)

int main() {
    random_device rd;
    mt19937 g(rd());

    int score = 0;
    // 퀴즈에 이용되는 vector
    vector<CVI> cvi;
    cvi.push_back(CVI("접종 후 15~30분 동안 접종기관에 머무르며 이상반응이 나타나는지 관찰하기", "1"));
    cvi.push_back(CVI("귀가 후 최소 1시간 이상 안정을 취하며 이상반응이 나타나는지 관찰하기", "2"));
    cvi.push_back(CVI("접종 후 최소 3일동안 특별한 증상이 나타는지 관찰하기", "1"));
    cvi.push_back(CVI("접종 당일과 다음날은 과격한 운동은 피하기", "1"));
    cvi.push_back(CVI("접종 후 다음날 부터 음주 가능", "2"));
    cvi.push_back(CVI("접종 당일 목욕은 해도 괜찮음", "2"));
    cvi.push_back(CVI("접종 부위 청결 유지", "1"));
    cvi.push_back(CVI("어르신의 경우 접종 후 혼자 있지 말고 다른사람과 같이 있어 증상 발생 시 도움 받을 수 있도록 하기", "1"));
    cvi.push_back(CVI("접종 후 39도 이상 고열이 있거나 평소와 다른 신체 증상 발생시, 바로 의사의 진료 받기", "1"));
    cvi.push_back(CVI("자신의 알레르기 여부를 알릴 필요는 없다.", "2"));
    cvi.push_back(CVI("코로나 확진자 밀착접촉이나 양성반응 의심시에도 백신을 맞으면 된다.", "2"));
    cvi.push_back(CVI("아이 접종 시 아무 보호자와 미접종 형제를 동반하여도 된다.", "2"));
    cvi.push_back(CVI("접종 후 3주차에 다리가 붓고 가슴통증이 있다면 의료기관을 방문해야 한다. ", "1"));


    // 시작화면 UI
    cout << "★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★\n";
    cout << "★                                                                                          ★\n";
    cout << "★                                        ■                                                ★\n";
    cout << "★                                        ■                                                ★\n";
    cout << "★                                    ■■■■■                                            ★\n";
    cout << "★                                        ■                                                ★\n";
    cout << "★                                        ■                                                ★\n";
    cout << "★                                                                                          ★\n";
    cout << "★                          CVI(Covid_19 Vaccine Information)                               ★\n";
    cout << "★                                                                                          ★\n";
    cout << "★                                                                                          ★\n";
    cout << "★     본 프로그램은 코로나 백신 접종 전, 후에 관련된 정보와                                ★\n";
    cout << "★     접종 후 자신에게 나타나는 증상에 대한 정보 및 대처방안과                             ★\n";
    cout << "★     백신 접종 후 주의사항을 상기하기 위한 퀴즈게임이 있는 프로그램입니다.                ★\n";
    cout << "★                                                                                          ★\n";
    cout << "★                                                                                          ★\n";
    cout << "★                                                                                          ★\n";
    cout << "★  --------------------------------------------------------------------------              ★\n";
    cout << "★  | < 사용 설명서 >                                                        |              ★\n";
    cout << "★  | 1. 1번~4번 항목이 있습니다.                                            |              ★\n";
    cout << "★  |                                                                        |              ★\n";
    cout << "★  | 2. 1번 입력시, 백신 접종 후 증상에 대한 정보를 제공합니다.             |              ★\n";
    cout << "★  |    (더 이상 필요가 없을 시, 1번 입력)                                  |              ★\n";
    cout << "★  |                                                                        |              ★\n";
    cout << "★  | 3. 2번 입력시, 자신의 증상을 입력하면 그에 대한 다양한                 |              ★\n";
    cout << "★  |    정보를 제공합니다. (더 이상 필요가 없을 시, 2번 입력)               |              ★\n";
    cout << "★  |                                                                        |              ★\n";
    cout << "★  | 4. 3번 입력시, 증상 후 주의사항을 상기하기 위해서                      |              ★\n";
    cout << "★  |    간단한 퀴즈게임 실행. (게임 종료를 원할 시 exit 입력)               |              ★\n";
    cout << "★  |                                                                        |              ★\n";
    cout << "★  | 5. 4번 입력시, 프로그램이 종료됩니다.                                  |              ★\n";
    cout << "★  --------------------------------------------------------------------------              ★\n";
    cout << "★                                                                                          ★\n";
    cout << "★                                                                                          ★\n";
    cout << "★                                                                                          ★\n";
    cout << "★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★\n";


    while (true) {
        string eng;
        // 기능별 안내 UI
        cout << "\n";
        cout << "              =================================================================\n";
        cout << "              |                                                               |\n";
        cout << "===============      ---  ---  ---  ---  ---  ---  ---  ---  ---  ---  ---    ===============\n";
        cout << "|             |                                                               |             |\n";
        cout << "|             |                                                               |             |\n";
        cout << "|             |          정보:1, 증상입력:2, 주의사항퀴즈:3, 종료:4           |             |\n";
        cout << "|             |                                                               |             |\n";
        cout << "|             |                                                               |             |\n";
        cout << "|             |                                                               |             |\n";
        cout << "|             |             < 주의사항 : 숫자만 입력해주세요! >               |             |\n";
        cout << "|             |                                                               |             |\n";
        cout << "===============      ---  ---  ---  ---  ---  ---  ---  ---  ---  ---  ---    ===============\n";
        cout << "              |                                                               |\n";
        cout << "              =================================================================\n";
        cout << "\n";
        cout << "원하시는 항목의 숫자를 입력해주세요! : ";
        int num = int_input();

        switch (num) {
        case 1: // 코로나 백신 접종 정보!
            // 백신 접종 관련 정보 UI 및 내용

            cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
            cout << "+                                                                                     +\n";
            cout << "+          코로나 백신 접종 전 주의사항                                               +\n";
            cout << "+                                                                                     +\n";
            cout << "+   1)건강상태가 좋을 때 코로나19 백신을 접종받는 것이 중요합니다.                    +\n";
            cout << "+   2)접종 전 반드시 의사의 예진을 받아야 합니다.                                     +\n";
            cout << "+   3)코로나19 백신 구성성분에 대한 알레르기가 있는 경우 접종을 받아서는 안됩니다.    +\n";
            cout << "+   4)코로나19 감염이 의심되는 경우 선별진료소 등을 통해 신속히 진단검사를 받으시고,  +\n";
            cout << "+     결과가 나올 때까지 예방접종을 연기합니다.                                       +\n";
            cout << "+   5)격리 중인 코로나19 환자 및 접촉자는 격리해제 될 때까지 예방접종을 연기합니다.   +\n";
            cout << "+   6)아이는 건강상태를 가장 잘 알고 있는 사람과 접종을 시행합니다.                  +\n";
            cout << "+                                                                                     +\n";
            cout << "+                                                                                     +\n";
            cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";

            cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
            cout << "+                                                                                     +\n";
            cout << "+          코로나 백신 접종 후 주의사항                                               +\n";
            cout << "+                                                                                     +\n";
            cout << "+   1)예방접종 후 15~30분간 접종기관에 머물러 이상반응 발생 여부를 관찰합니다.        +\n";
            cout << "+   2)예방접종 후 3시간 이상 주의 깊게 관찰합니다.                                    +\n";
            cout << "+   3)최소 3일 정도는 특별한 관심을 가지고 관찰하며 평소와 다른 신체 증상이 나타나면  +\n";
            cout << "+     바로 의사의 진료를 받도록 합니다.                                               +\n";
            cout << "+   4)예방접종 후 일주일 정도는 고강도 운동 및 활동, 음주를 삼가주세요.               +\n";
            cout << "+   5)접종부위는 청결히 유지합니다.                                                   +\n";
            cout << "+   6)어르신은, 예방접종 후 혼자 있지 말고 다른 사람과 함께 있어 증상 발생 시         +\n";
            cout << "+      바로 도움을 받을 수 있도록 합니다.                                             +\n";
            cout << "+                                                                                     +\n";
            cout << "+                                                                                     +\n";
            cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";

            cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
            cout << "+                                                                                     +\n";
            cout << "+          코로나 백신 접종 후 위험 증상                                              +\n";
            cout << "+                                                                                     +\n";
            cout << "+   1)접종부위 부기,통증,발적이 48시간 이후에도 악화되는 경우                         +\n";
            cout << "+   2)4주 내 호흡곤란,흉통,지속적인 복부 통증, 다리붓기와 같은 증상이 나타난 경우     +\n";
            cout << "+   3)최소 3일 정도는 특별한 관심을 가지고 관찰하며 평소와 다른 신체 증상이 나타나면  +\n";
            cout << "+   4)심하거나 2일 이상의 지속적인 두통이 발생하고, 진통제에 반응하지 않거나          +\n";
            cout << "+     조절되지 않는 경우 또는 시야가 흐려지는 경우                                    +\n";
            cout << "+   5)갑자기 기운이 떨어지거나 평소와 다른 이상증상이 나타난 경우                     +\n";
            cout << "+   6)접종부위가 아닌 곳에서 멍이나 출혈이 발생한 경우                                +\n";
            cout << "+         1~6과 같은 경우 의사의 진료가 필요합니다.                                   +\n";
            cout << "+                                                                                     +\n";
            cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";

            cout << "\n시작화면으로 돌아가려면 숫자1번을 바로 다음 단계를 원하신다면 아무 숫자를 눌러주세요 : "; // 종료가 아닌 시작화면으로 돌아감
            num = int_input();
            if (num == 1)
                break;

        case 2: // 코로나 백신 접종 후 자신에게 나타난 증상!
            // 자신의 증상에 대한 정보 제공 UI
            cout << "□□□□□□□□□□□□□□□□□□□□□□□□□□□□  \n";
            cout << "□                                                    □  \n";
            cout << "□    코로나 백신 접종 후 당신에게 나타난 증상은?     □  \n";
            cout << "□                                                    □  \n";
            cout << "□    → 화면에 출력되는 항목이 해당이 되면 : o       □  \n";
            cout << "□    → 화면에 출력되는 항목이 해당이 안되면 : x     □  \n";
            cout << "□    → 대소문자 상관없어요!!                        □  \n";
            cout << "□    → 다른값 입력시, 해당항목에 대해 다시 입력!    □  \n";
            cout << "□    → 자신의 증상에 관한 내용이 없다면             □  \n";
            cout << "□       의료기관, 보건소에 연락하고 방문하세요!      □  \n";
            cout << "□                                                    □  \n";
            cout << "□□□□□□□□□□□□□□□□□□□□□□□□□□□□  \n";

            symptoms();
            cout << "\n";
            cout << "□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n";
            cout << "\n시작화면으로 돌아가려면 숫자2번을 바로 다음 단계를 원하신다면 아무 숫자를 눌러주세요 : ";  // 종료가 아닌 시작화면으로 돌아감
            num = int_input();
            if (num == 2)
                break;

        case 3: // 코로나 백신 접종 후 주의사항에 대한 퀴즈게임!
            int random;
            while (true) {
                string c;
                // 퀴즈게임 UI
                cout << "\n";
                cout << "        ll  \n";
                cout << "        ll  \n";
                cout << "       ■■  \n";
                cout << "       ■■       " << "★★▣       주의사항 퀴즈 게임       ▣★★\n";
                cout << "     ■■■■     " << "★  < 백신접종 후 주의사항 관련 퀴즈! >   ★\n";
                cout << "     ■■■■     " << "★  < 문항을 보고 옳은 답을 입력해! >     ★\n";
                cout << "     ■■■■     " << "★         → 맞으면 숫자 1번입력!        ★\n";
                cout << "     ■■■■     " << "★         → 틀리면 숫자 2번입력!        ★\n";
                cout << "     ■■■■     " << "★         → 다른숫자 혹은 다른 값       ★\n";
                cout << "  ■■■■■■■  " << "★            입력할시 틀린것으로 간주!   ★\n";
                cout << "       ■■       " << "★         → 현재 문항갯수 : 13개        ★\n";
                cout << "       ■■       " << "★         → 나가기 exit                 ★\n";
                cout << "       ■■       " << "★         → 입력하기.                   ★\n";
                cout << "     ■■■■     " << "★★★★★★★★★★★★★★★★★★★★★★\n"; // 퀴즈 사용법 수정
                

                
                vector<int> questions;
                for (int i = 0; i < cvi.size(); i++) {
                    questions.push_back(i);
                }
                shuffle(questions.begin(), questions.end(), g);

                for (int index : questions) {
                    cout << "      SCORE" << "[" << score << "]\n";
                    cout << "      문제:";
                    cout << cvi.at(index).getState();
                    cout << "\n";
                    cout << "      정답은 무엇인가요!! : ";
                    cin >> c;
                    if (c == "exit") // exit입력하면 프로그램 처음부터 다시 시작
                        break;
                    else if (cvi.at(index).getSolution() == c) {    // 입력받은 답이 맞으면 정답UI 출력

                        score += 1; // score기능 추가
                        // 정답일 경우 UI
                        cout << "                  ★★★★★★★★★  \n";
                        cout << "               ★★★★★★★★★★★★ \n";
                        cout << "            ★★★                 ★★★\n";
                        cout << "          ★★★                      ★★★\n";
                        cout << "        ★★★                          ★★★\n";
                        cout << "       ★★★                            ★★★\n";
                        cout << "      ★★★                              ★★★\n";
                        cout << "     ★★★                                ★★★\n";
                        cout << "     ★★★             정답!!!            ★★★\n";
                        cout << "     ★★★                                ★★★\n";
                        cout << "      ★★★                              ★★★\n";
                        cout << "       ★★★                            ★★★\n";
                        cout << "        ★★★                          ★★★\n";
                        cout << "          ★★★                      ★★★\n";
                        cout << "            ★★★                  ★★★\n";
                        cout << "               ★★★★★★★★★★★★ \n";
                        cout << "                  ★★★★★★★★★  \n\n";
                    }
                    else // 입력받은 답이 맞지 않으면 오답UI 출력
                    {
                        score -= 1;
                        if (score < 0)
                        {
                            score = 0;
                        }
                        // 오답일 경우 UI
                        cout << "    ★★★                ★★★\n";
                        cout << "     ★★★              ★★★\n";
                        cout << "      ★★★            ★★★\n";
                        cout << "       ★★★          ★★★\n";
                        cout << "        ★★★        ★★★\n";
                        cout << "         ★★★      ★★★\n";
                        cout << "          ★★★    ★★★\n";
                        cout << "           ★★★★★★★\n";
                        cout << "            ★★★★★★\n";
                        cout << "           ★★★★★★★\n";
                        cout << "          ★★★    ★★★\n";
                        cout << "         ★★★      ★★★\n";
                        cout << "        ★★★        ★★★\n";
                        cout << "       ★★★          ★★★\n";
                        cout << "      ★★★            ★★★    오답입니다.. 주의사항을 다시 한 번 숙지해주세요.\n";
                        cout << "     ★★★              ★★★\n";
                        cout << "    ★★★                ★★★\n\n";


                    }
                }

                if (c == "exit") {
                    break;
                }
                cout << "\n";
                cout << "최종점수 :" << score << "점\n";
                cout << "★★▣       주의사항 퀴즈 게임       ▣★★\n"; // UI추가
                cout << "★         모든 문제가 끝났습니다.        ★\n"; //점수 기능, 최종 점수 알림, 게임 다시 시작기능 추가 수정
                cout << "★     다시 시작하고 싶으시다면 3번을     ★\n";
                cout << "★       게임을 종료하고 싶으시다면       ★\n";
                cout << "★          exit을 입력해주세요.          ★\n";
                cout << "★★★★★★★★★★★★★★★★★★★★★★\n";
                do {
                    cout << " > ";
                    cin >> c;
                } while (c != "3" && c != "exit");

                if (c == "exit") {
                    break;
                }
            }
            break;

        case 4: // 프로그램 종료!
            // 프로그램 종료 UI
            cout << "\n";
            cout << "▣〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓▣\n";
            cout << "▣                   ■■  ■■                   ▣\n";
            cout << "▣                 ■    ■    ■                 ▣\n";
            cout << "▣                 ■          ■                 ▣\n";
            cout << "▣                   ■      ■                   ▣\n";
            cout << "▣                    ■    ■                    ▣\n";
            cout << "▣                      ■■                      ▣\n";
            cout << "▣                       ■                       ▣\n";
            cout << "▣                                                ▣\n";
            cout << "▣             사용해주셔서 감사합니다!           ▣\n";
            cout << "▣                                                ▣\n";
            cout << "▣             모두들 코로나19로 인해             ▣\n";
            cout << "▣                                                ▣\n";
            cout << "▣                많이 힘드실텐데                 ▣\n";
            cout << "▣                                                ▣\n";
            cout << "▣             우리 모두 같이 힘내요!             ▣\n";
            cout << "▣                                                ▣\n";
            cout << "▣                                                ▣\n";
            cout << "▣〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓▣\n";
            return 0;
        default: // 예외처리(기능 1~4 외에 다른 숫자 입력 시 예외처리)
            // 예외처리 UI
            cout << "\n";
            cout << "              =================================================================\n";
            cout << "              |                                                               |\n";
            cout << "===============      ---  ---  ---  ---  ---  ---  ---  ---  ---  ---  ---    ===============\n";
            cout << "|             |                                                               |             |\n";
            cout << "|             |                 ■■■■■■     ■■■■■■                 |             |\n";
            cout << "|             |                   ■   ■          ■   ■                    |             |\n";
            cout << "|             |                   ■   ■          ■   ■                    |             |\n";
            cout << "|             |                                                               |             |\n";
            cout << "|             |                   다른 숫자를 입력하셨군요...ㅠㅠ!            |             |\n";
            cout << "|             |                                                               |             |\n";
            cout << "|             |             1번, 2번, 3번, 4번 중에서 입력해주세요!           |             |\n";
            cout << "===============      ---  ---  ---  ---  ---  ---  ---  ---  ---  ---  ---    ===============\n";
            cout << "              |                                                               |\n";
            cout << "              =================================================================\n";
            cout << "\n";
            cout << "다시 안내해드릴게요!\n";
            cout << "\n";
            break;
        }
    }
} // 전체적인 프로그램 코드 구성_최**
  // 검토 완료_김**,전**,최**

