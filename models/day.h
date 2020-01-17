struct Date{
    int day,month,year;
};

class Day{
    private:
        Date today;
        bool setToday();
    public:
        char attendance[200];
        Day();
        Date getToday();

};
