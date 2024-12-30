#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std; // namespace std 사용

class Book {
public:
    string title;
    string author;

    Book(const string& title, const string& author)
        : title(title), author(author) {}
};

class BookManager {
private:
    vector<Book> books; // 책 목록 저장

public:
    // 책 추가 메서드
    void addBook(const string& title, const string& author) {
        if(nullptr != findBookByTitle(title))
        {
            cout << "동일한 이름의 책이 존재합니다. 책이 추가되지 않습니다.";
            return;
        }

        books.push_back(Book(title, author)); // push_back 사용
        cout << "책이 추가되었습니다: " << title << " by " << author << endl;
    }

    // 모든 책 출력 메서드
    void displayAllBooks() const {
        if (books.empty()) {
            cout << "현재 등록된 책이 없습니다." << endl;
            return;
        }

        cout << "현재 도서 목록:" << endl;
        for (size_t i = 0; i < books.size(); i++) { // 일반적인 for문 사용
            cout << "- " << books[i].title << " by " << books[i].author << endl;
        }
    }

    Book* getBookByTitle(const string& title)
    {
        Book* result = findBookByTitle(title);
        if(nullptr == result)
        {
            cout << "해당하는 책을 찾을 수 없습니다." << endl;
        }

        return result;
    }

    Book* getBookByAuthor(const string& author)
    {
        Book* result = findBookByAuthor(author);
        if (nullptr == result)
        {
            cout << "해당하는 책을 찾을 수 없습니다." << endl;
        }

        return result;
    }

private:
    Book* findBookByTitle(const string& title)
    {
        Book* result = nullptr;
        for (size_t IDX = 0; IDX < books.size(); ++IDX)
        {
            if (title == books[IDX].title)
            {
                result = &books[IDX];
                break;
            }
        }

        return result;
    }

    Book* findBookByAuthor(const string& author)
    {
        Book* result = nullptr;
        for (size_t IDX = 0; IDX < books.size(); ++IDX)
        {
            if (author == books[IDX].author)
            {
                result = &books[IDX];
                break;
            }
        }

        return result;
    }
};

class BorrowManager
{
private:
    unordered_map<string, int> stock;

public:
    void initializeStock(Book book, int quantity = 3)
    {
        if(stock.find(book.title) != stock.end())
        {
            cout << "재고 추가가 실패했습니다." << endl;
            return;
        }

        stock.insert(make_pair(book.title, quantity));
        cout << "추가된 책 제목 : " << book.title << " 재고 : " << quantity << endl;
    }

    void borrowBook(const string& title)
    {
        auto book = stock.find(title);
        if(book != stock.end() && book->second > 0)
        {
            cout << book->first << " 책을 빌렸습니다." << endl;
            cout << "남은 재고 : " << --(book->second) << endl;
        }
        else if(book == stock.end())
        {
            cout << book->first << " 책이 존재하지 않습니다." << endl;
        }
        else
        {
            cout << book->first << " 책이 전부 대여 중입니다." << endl;
        }
    }

    void returnBook(const string& title)
    {
        auto book = stock.find(title);
        if(book != stock.end() && book->second < 3)
        {
            cout << "책을 반납했습니다." << endl;
            cout << book->first << " 의 " << "남은 재고 : " << ++(book->second) << endl;
        }
        else
        {
            cout << book->first << " 는 여기서 빌린 책이 아닌 것 같습니다." << endl;
        }
    }

    void displayStock()
    {
        cout << "현재 도서 재고 현황:" << endl;
        auto iterBegin = stock.begin();
        auto iterEnd = stock.end();
        while(iterBegin != iterEnd)
        {
            cout << "- " << iterBegin->first << " 재고 : " << iterBegin->second << endl;
            ++iterBegin;
        }
    }
};

int main() {
    BookManager manager;
    BorrowManager borrowManager;

    // 도서관 관리 프로그램의 기본 메뉴를 반복적으로 출력하여 사용자 입력을 처리합니다.
    // 프로그램 종료를 선택하기 전까지 계속 동작합니다.
    while (true) {
        cout << "\n도서관 관리 프로그램" << endl;
        cout << "1. 책 추가" << endl; // 책 정보를 입력받아 책 목록에 추가
        cout << "2. 모든 책 출력" << endl; // 현재 책 목록에 있는 모든 책 출력
        cout << "3. 모든 재고 출력" << endl; // 현재 책 재고 목록에 있는 모든 책과 해당 책의 재고 출력
        cout << "4. 제목으로 책 대여하기" << endl; // 현재 책 재고 목록에 있는 책 중 일치하는 제목의 책 대여하기
        cout << "5. 저자 이름으로 책 대여하기" << endl; // 현재 책 재고 목록에 있는 책 중 일치하는 저자의 책 대여하기
        cout << "6. 빌린 책 반납하기" << endl; // 빌린 책의 제목과 일치하는 책 반납하기
        cout << "7. 제목으로 책의 존재 여부 출력" << endl; // 현재 책 목록에 있는 책 중 일치하는 제목의 책이 있는지 출력
        cout << "8. 저자 이름으로 책의 존재 여부 출력" << endl; // 현재 책 목록에 있는 책 중 일치하는 저자의 책이 있는지 출력
        cout << "0. 종료" << endl; // 프로그램 종료
        cout << "선택: ";

        int choice; // 사용자의 메뉴 선택을 저장
        cin >> choice;

        if (choice == 1) {
            // 1번 선택: 책 추가
            // 사용자로부터 책 제목과 저자명을 입력받아 BookManager에 추가합니다.
            string title, author;
            cout << "책 제목: ";
            cin.ignore(); // 이전 입력의 잔여 버퍼를 제거
            getline(cin, title); // 제목 입력 (공백 포함)
            cout << "책 저자: ";
            getline(cin, author); // 저자명 입력 (공백 포함)
            manager.addBook(title, author); // 입력받은 책 정보를 추가
            Book* book = manager.getBookByTitle(title);
            if(book)
            {
                borrowManager.initializeStock(*book, 3);
            }
        }
        else if (choice == 2) {
            // 2번 선택: 모든 책 출력
            // 현재 BookManager에 저장된 책 목록을 출력합니다.
            manager.displayAllBooks();
        }
        else if (choice == 3)
        {
	        // 3번 선택: 모든 책의 재고 출력
            // 현재 BorrowManager에 저장된 책 목록과 재고를 출력합니다.
            borrowManager.displayStock();
        }
        else if (choice == 4)
        {
            // 4번 선택: 제목으로 책 대여하기
            // 현재 BorrowManager에 저장된 책 중 일치하는 제목의 책을 대여합니다.
            string title;
            cout << "찾고자 하는 책 제목: ";
            cin.ignore();
            getline(cin, title);
            Book* book = manager.getBookByTitle(title);
            if(book)
            {
            	borrowManager.borrowBook(book->title);
            }
        }
        else if (choice == 5)
        {
            // 5번 선택: 작가 이름으로 책 대여하기
            // 현재 BorrowManager에 저장된 책 중 일치하는 저자의 책을 대여합니다.
            // 여러 권이라면 책을 선택할 수 있도록 합니다.
            string author;
            cout << "찾고자 하는 책의 저자: ";
            cin.ignore();
            getline(cin, author);
            Book* book = manager.getBookByAuthor(author);
            if (book)
            {
                borrowManager.borrowBook(book->title);
            }
        }
        else if (choice == 6)
        {
            // 6번 선택: 책의 제목으로 책 반납하기
            // 현재 BorrowManager에 저장된 책 목록 중 제목에 해당하는 책이면 반납합니다.
            string title;
            cout << "반납하고자 하는 책 제목: ";
            cin.ignore();
            getline(cin, title);
            borrowManager.returnBook(title);
        }
        else if (choice == 7)
        {
	        // 7번 선택: 제목으로 책 검색
            // 현재 BookManager에 저장된 책 목록 중 제목에 해당하는 책을 찾아 있는 책인지 알아냅니다.
            string title;
            cout << "찾고자 하는 책 제목: ";
            cin.ignore();
            getline(cin, title);
            manager.getBookByTitle(title);
        }
        else if (choice == 8)
        {
            // 8번 선택: 저자 이름으로 책 검색
            // 현재 BookManager에 저장된 책 목록 중 저자 이름에 해당하는 책을 찾아 있는 책인지 알아냅니다.
            string author;
            cout << "찾고자 하는 책의 저자 이름: ";
            cin.ignore();
            getline(cin, author);
            manager.getBookByAuthor(author);
        }
        else if (choice == 0) {
            // 3번 선택: 종료
            // 프로그램을 종료하고 사용자에게 메시지를 출력합니다.
            cout << "프로그램을 종료합니다." << endl;
            break; // while 루프 종료
        }
        else {
            // 잘못된 입력 처리
            // 메뉴에 없는 번호를 입력했을 경우 경고 메시지를 출력합니다.
            cout << "잘못된 입력입니다. 다시 시도하세요." << endl;
        }
    }

    return 0; // 프로그램 정상 종료
}