//*******************************************IMPLEMENTATION COUNTRY*******************************************//
template <class type, class E>
void CountryGraph <type, E> :: makeDistancesInfinite() {
    for(auto &it : this->cityList) {
        // Тут была ошибка 1, не double а int
        it->distance = numeric_limits <int> :: max();
    }
}

template <class type, class E>
void CountryGraph <type, E> :: printCountry() {
    for(const auto &city : this->cityList) {
        city->printCity();
        cout << endl << endl;
    }
}

template <class type, class E>
bool CountryGraph <type, E> :: cityInCountry(const string &name) {
    for (const auto& it : cityList) {
        if(it->name == name)
            return true;
    }
    return false;
}

template <class type, class E>
bool CountryGraph <type, E> :: areAllBlack() {
    for(const auto &it : cityList) {
        if (it->current_color != color :: black)
            return false;
    }
    return true;
}

template <class type, class E>
void CountryGraph <type, E> :: whitewashAll() {
    for(auto &it : cityList) {
        it->current_color = color :: white;
    }
}

template <class type, class E>
shared_ptr <City<type>> CountryGraph <type, E> :: getPtr(const string &name) {
    for(const auto &it : cityList) {
        if(it->name == name)
            return it;
    }
    return nullptr;
}

template <class type, class E>
void CountryGraph <type, E> :: insertCity(const string &cityName) {
    if(!cityInCountry(cityName)) {
        auto ptr = make_shared <City<type>>(cityName);
        cityList.push_back(ptr);
    }
}

template <class type, class E>
void CountryGraph <type, E> :: insertCities(const vector <string> &cities) {
    for (const auto& it : cities) {
        this->insertCity(it);
    }
}

template <class type, class E>
void CountryGraph <type, E> :: addRoad(const string& city1, const string& city2, double price) {
    auto firstCity = this->getPtr(city1);
    auto secondCity = this->getPtr(city2);

    if(firstCity == nullptr)
        throw "city " + city1 + " does not exist(road insertion)";
    if(secondCity == nullptr)
        throw "city " + city2 + " does not exist(road insertion)";

    roadsPrice[city1][city2] = price;
    roadsPrice[city2][city1] = price;

    firstCity->addRoadTo(city2, secondCity);
    firstCity->addRoadFrom(city2, secondCity);

    secondCity->addRoadTo(city1, firstCity);
    secondCity->addRoadFrom(city1, firstCity);
//success
}

template <class type, class E>
void CountryGraph <type, E> :: addRailway(const string &city1, const string &city2, double price) {
    auto firstCity = this->getPtr(city1);
    auto secondCity = this->getPtr(city2);

    if(firstCity == nullptr)
        throw "city " + city1 + " does not exist(railway insertion)";
    if(secondCity == nullptr)
        throw "city " + city2 + " does not exist(railway insertion)";

    railwaysPrice[city1][city2] = price;
    railwaysPrice[city2][city1] = price;

    firstCity->addRailwayTo(city2, secondCity);
    firstCity->addRailwayFrom(city2, secondCity);

    secondCity->addRailwayTo(city1, firstCity);
    secondCity->addRailwayFrom(city1, firstCity);
}

template <class type, class E>
double CountryGraph <type, E> :: findTheCheapestWay(const string &start, const string &finish) {
    if(!cityInCountry(start))
        throw "city" + start + "does not exist";
    if(!cityInCountry(finish))
        throw "city" + finish + "does not exist";

    // Everything like in Dijkstra algorithm
    this->makeDistancesInfinite();
    this->getPtr(start)->distance = 0;

    this->whitewashAll();

    while(!areAllBlack()) {
        this->processing();
    }

    auto finishPtr = getPtr(finish);
    return finishPtr->distance;
}

template <class type, class E>
void CountryGraph <type, E> :: processing() {
    // Сначала ищем город с минимальной меткой дистанции, сначала это стартовый город
    auto ourCityPtr = this->findMinDistanceCity();
    string ourCityName = ourCityPtr->name;
    double ourCityDistance = ourCityPtr->distance;
    Travel ourCityTravelType = ourCityPtr->previousTravel;

    //ВЫНЕСТИ СОДЕРЖИМОЕ FOR В ОТДЕЛЬНУЮ ФУНКЦИЮ
    // Сначала мы ищем кратчайший путь по всем дорогам, применяя скидку, где она есть
    for(auto &it : ourCityPtr->roads_to) {
        string neighbourName = it.first;
        auto neighbourPtr = it.second;

        double apply_discount = (ourCityTravelType == Travel :: road) ? (this->applyDiscount) : (1);
        double currentRoadPrice = this->roadsPrice[ourCityName][neighbourName];

        double candidate1 = ourCityDistance + currentRoadPrice * apply_discount;
        double candidate2 = it.second->distance;

        neighbourPtr->distance = min(candidate1, candidate2);
    }

    // А после этого ищем эти пути по железным дорогам, и если они дешевле, вдруг, то они обновятся
    for(auto &it : ourCityPtr->railways_to) {
        string neighbourName = it.first;
        auto neighbourPtr = it.second;

        double apply_discount = (ourCityTravelType == Travel :: railway) ? (this->applyDiscount) : (1);
        // Тут была ошибка номер 2
        double currentRoadPrice = this->railwaysPrice[ourCityName][neighbourName];

        double candidate1 = ourCityDistance + currentRoadPrice * apply_discount;
        double candidate2 = it.second->distance;

        neighbourPtr->distance = min(candidate1, candidate2);
    }

    ourCityPtr->current_color = color :: black;
}

template <class type, class E>
shared_ptr <City<type>>  CountryGraph <type, E> :: findMinDistanceCity() {
    double min = numeric_limits <int> :: max();
    shared_ptr <City<type>> answer = nullptr;
    string name;
    double distance;
    color curColor;

    for(auto& it : cityList) {

        name = it->name;
        distance = it->distance;
        curColor = it->current_color;

        if((curColor == (color :: white)) && (distance < min)) {
            answer = it;
            min = it->distance;
        }
    }
    return answer;
}
//*******************************************IMPLEMENTATION COUNTRY END***************************************//


//*******************************************IMPLEMENTATION CITY**********************************************//
template <class type>
City <type> :: City() {
    this->name = "noname";
    this->data = 0;
    this->current_color = color :: white;
    this->previousTravel = Travel :: nohow;
    this->time_in = -1;
    this->time_out = -1;
}

template <class type>
City <type> :: City(const string &name) {
    this->name = name;
    this->data = 0;
    this->current_color = color :: white;
    this->previousTravel = Travel :: nohow;
    this->time_in = -1;
    this->time_out = -1;
}

template <class type>
void City <type> :: addRoadTo(string name, shared_ptr <City<type>> pointer) {
    this->roads_to[name] = shared_ptr <City<type>>(pointer);
    return;
}

template <class type>
void City <type> :: addRoadFrom(string name, shared_ptr <City<type>> pointer) {
    this->roads_from[name] = shared_ptr <City<type>>(pointer);
    return;
}

template <class type>
void City <type> :: addRailwayTo(string name, shared_ptr <City<type>> pointer) {
    this->railways_to[name] = shared_ptr <City<type>>(pointer);
    return;
}

template <class type>
void City <type> :: addRailwayFrom(string name, shared_ptr <City<type>> pointer) {
    this->railways_from[name] = shared_ptr <City<type>>(pointer);
    return;
}

template <class type>
void City <type> :: printCity() {
    cout << "City " << this->name << endl;
    cout << "Roads to :"; this->printRoads();
    cout << "Railways to : "; this->printRailways();

}

template <class type>
void City <type> :: printRailways() {
    for(const auto &railway : railways_to) {
        cout << railway.first << " ";
    }
}
using namespace std;
template <class type>
void City <type> :: printRoads() {
    for(const auto &road : roads_to) {
        cout << road.first << " ";
    }
    cout << endl;
}

//*******************************************IMPLEMENTATION CITY END******************************************//
