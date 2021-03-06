#include "./Guard.h"

Guard::~Guard()
{
	player1 = nullptr;
	player2 = nullptr;
	patroldeck = nullptr;
	alarms = nullptr;
	
}

void Guard::setFloorMap(vector<Coord> floor[4][4])
{
	for (unsigned i = 0; i < 4; i++)
	{
		for (unsigned j = 0; j < 4; j++)
			this->floor[j][i] = floor[j][i];
	}
}

void Guard::checkPlayer(PlayerInterface * p)
{
	for (auto &it : p->getVisibleFrom())
	{
		if (it == pos)
		{
			p->removeStealthToken();
			break;
		}
	}
}

// guard checks if in his current position a player is found
void Guard::GuardCheck()
{
		for (auto &it : player1->getVisibleFrom())
		{
			if (it == pos)
			{
				player1->removeStealthToken();
				break;
			}
		}

		for (auto &it : player2->getVisibleFrom())
		{
			if (it == pos)
			{
				player2->removeStealthToken();
				break;
			}
		}
}

void Guard::print()
{
	cout << "Current guard position: " << pos << endl;
	DEBUG_MSG("Current guard position: " << pos);
	if(patroldeck->activeCard() != nullptr) DEBUG_MSG("Active patrol card: " << patroldeck->activeCard()->getDescription());
/*	DEBUG_MSG("Steps to finish turn: " << currsteps);
	DEBUG_MSG("Current path:");
	for (auto& a : path)
	{
		DEBUG_MSG(a);
	}*/
}

void Guard::locateGuard()
{
	if (currsteps == 0 && !(pos == NPOS))
	{
		SetCurrSteps();
		//DEBUG_MSG("Current steps " << currsteps<< endl);
	}
	positionGuard();
	notify();
}

void Guard::positionGuard()
{
	PatrolCard * p;
	if (pos == NPOS)
	{
		p = static_cast<PatrolCard*>(patroldeck->next());
		pos = p->getCoord();
		cout << "Guard starts in" << pos << endl;
		//DEBUG_MSG("Guard start pos " << pos << endl);
		p = static_cast<PatrolCard*>(patroldeck->next());
		expectedMov = p->getCoord();
		cout << "First guard expected movement" << expectedMov << endl;
		this->GuardCheck();
		target = expectedMov;
		notify();
		//DEBUG_MSG("First guard target " << target << endl);
	}
}

bool Guard::move()
{
	PatrolCard * p;
	FindPath(pos);
	cout << "Guard is moving towards " << target << endl;
	if (!path.empty() && currsteps > 0)
	{
		pos = path.front();
		this->GuardCheck();
		//DEBUG_MSG("Guard has moved to" << pos << endl);
		if (currsteps > 0)
			currsteps--;
		//DEBUG_MSG("Remaining steps " << currsteps);
	}
	if (pos == expectedMov)
	{
		if (patroldeck->isEmpty())
		{
			patroldeck->reset();
			this->increaseSpeed();
		}
		p = static_cast<PatrolCard*>(patroldeck->next());
		expectedMov = p->getCoord();
	}
	removeAlarm(pos);
	FindPath(pos);
	notify();
	
	if (currsteps == 0)
	{
		//DEBUG_MSG("Guard turn has ended\n");
		return false;
	}
	else return true;
}
bool Guard::removeAlarm(Coord c)
{
	if (find(alarms->begin(), alarms->end(), c) != alarms->end())
	{
		alarms->erase(std::remove(alarms->begin(), alarms->end(), c), alarms->end());
		//DEBUG_MSG("alarm removed from tile " << c << endl);
		return true;
	}
	else
	{
		//DEBUG_MSG("there was no alarm in tile " << c << endl);
		return false;
	}
}

bool Guard::FindPath(Coord const coord)
{
	path.clear();
	if ((coord.col) < 4 && (coord.row < 4))
	{
		vector<int> dist(16, INT_MAX);//vector that contains the distance required to go to any point in floor from current pos
		vector<int> parent(16, -1);// vector that contains prior room to be accessed following a path from current pos
		dist[toIndex(coord)] = 0;//set distance to current pos = 0
		queue<int> Q;
		Q.push(toIndex(coord));
		while (!Q.empty())
		{
			int index = Q.front();
			Q.pop();
			for (auto &it: floor[toCoord(index).col][toCoord(index).row])//search for all adjacents rooms to current one
			{
				if (dist[toIndex(it)] == INT_MAX) //if room was not visited
				{
					Q.push(toIndex(it));//add to queue
					dist[toIndex(it)] = dist[index] + 1;//and set distance equal to distance to parent room + 1
					parent[toIndex(it)] = index;
				}
			}
		}
		if (!alarms->empty())
		{
			target = toCoord(closestTarget(dist));
			shortestPath(toIndex(coord), closestTarget(dist), parent);
		}
		else
		{
			target = expectedMov;
			shortestPath(toIndex(coord), toIndex(expectedMov), parent);
		}
		/*DEBUG_MSG("Distances to each room" << endl);
		for (auto & a : dist)
			DEBUG_MSG(a << endl);
		DEBUG_MSG("Room connections from start pos:" << endl);
		for (auto & a : parent)
			DEBUG_MSG(a << endl);*/
		//DEBUG_MSG("Path is:" << endl);
		//for (auto& a : path)
			//DEBUG_MSG(a <<" ");
		//cout << endl;
		notify();
		return true;
	}
	return false;
}

bool Guard::shortestPath(unsigned const start, unsigned const end, vector<int> parent)
{
	if (start < parent.size() && end < parent.size())//check if end position is inside floor
	{
		if (start == end || end == -1);//if destination and source are the same, target was reached
			//path.push_front(toCoord(start));//es la direccion actual
		else {
			shortestPath(start, parent[end], parent);//if destination was not found, try again but with adjacent room from before
			path.push_back(toCoord(end));
		}
		return true;
	}
	return false;
}

unsigned Guard::closestTarget(vector<int> distances)
{

	unsigned shortDist = INT_MAX;
	unsigned destination = INT_MAX;
	if(alarms->empty()==false)
	{
		for (auto& al : *alarms)
		{
			if ((unsigned)distances[toIndex(al)] < shortDist)
			{
				shortDist = distances[toIndex(al)];
				destination = toIndex(al);
			}
		}
	}
	else destination = toIndex(expectedMov);
	//DEBUG_MSG(" closest target is in floor " << toCoord(destination) << "\n");
	return destination;
}