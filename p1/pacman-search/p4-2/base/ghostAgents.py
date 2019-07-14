# ghostAgents.py
# --------------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
#
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).


from game import Agent
from game import Actions
from game import Directions
import random
from util import manhattanDistance
import util

class GhostAgent( Agent ):
    def __init__( self, index ):
        self.index = index

    def getAction( self, state ):
        dist = self.getDistribution(state)
        if len(dist) == 0:
            return Directions.STOP
        else:
            return util.chooseFromDistribution( dist )

    def getDistribution(self, state):
        "Returns a Counter encoding a distribution over actions from the provided state."
        util.raiseNotDefined()

class RandomGhost( GhostAgent ):
    "A ghost that chooses a legal action uniformly at random."
    def getDistribution( self, state ):
        dist = util.Counter()
        for a in state.getLegalActions( self.index ): dist[a] = 1.0
        dist.normalize()
        return dist

class CustomGhost(GhostAgent):
    def run(self, gameState, path):
        walls = gameState.getWalls()
        ghosts = gameState.getGhostStates()

        m, n = len(walls.data), len(walls.data[0])
        x1, y1 = gameState.getPacmanPosition()
        x1, y1 = n - y1 - 1, x1
        data = '%i %i\n%s\n%i %i\n%s\n%i\n' % (n, m, walls, x1, y1, gameState.getFood(), len(ghosts))
        for x in ghosts:
            x2, y2 = x.configuration.pos
            x2, y2 = n - y2 - 1, x2
            data += '%i %i\n' % (x2, y2)
        data += '%i\n' % self.index
        open('../build/tmp.txt', 'w').write(data)
        fp = open('../build/log.txt', 'a')
        fp.write('Standard Input:\n')
        fp.write(data + '\n')
        exec_name = path
        t = subprocess.Popen(exec_name, stdin=PIPE, stdout=PIPE, stderr=PIPE)
        stdout_data, stderr_data = t.communicate(input=bytes(data))
        stdout_data = str(stdout_data).strip()
        stderr_data = str(stderr_data).strip()
        fp.write('Standard Output:\n')
        fp.write(stdout_data + '\n')
        fp.write('\nReturn Code:%i\n' % t.returncode)
        fp.close()
        assert t.returncode == 0
        from game import Directions
        mp = {'N':Directions.NORTH, 'S':Directions.SOUTH, 'W':Directions.WEST, 'E':Directions.EAST}
        if len(stdout_data) == 0:
            return Directions.STOP
        return mp[stdout_data[0]]

    def getDistribution( self, state ):
        dist = util.Counter()
        dist[self.run(state, '../build/ghost.out')]
        return dist

class DirectionalGhost( GhostAgent ):
    "A ghost that prefers to rush Pacman, or flee when scared."
    def __init__( self, index, prob_attack=0.8, prob_scaredFlee=0.8 ):
        self.index = index
        self.prob_attack = prob_attack
        self.prob_scaredFlee = prob_scaredFlee

    def getDistribution( self, state ):
        # Read variables from state
        ghostState = state.getGhostState( self.index )
        legalActions = state.getLegalActions( self.index )
        pos = state.getGhostPosition( self.index )
        isScared = ghostState.scaredTimer > 0

        speed = 1
        if isScared: speed = 0.5

        actionVectors = [Actions.directionToVector( a, speed ) for a in legalActions]
        newPositions = [( pos[0]+a[0], pos[1]+a[1] ) for a in actionVectors]
        pacmanPosition = state.getPacmanPosition()

        # Select best actions given the state
        distancesToPacman = [manhattanDistance( pos, pacmanPosition ) for pos in newPositions]
        if isScared:
            bestScore = max( distancesToPacman )
            bestProb = self.prob_scaredFlee
        else:
            bestScore = min( distancesToPacman )
            bestProb = self.prob_attack
        bestActions = [action for action, distance in zip( legalActions, distancesToPacman ) if distance == bestScore]

        # Construct distribution
        dist = util.Counter()
        for a in bestActions: dist[a] = bestProb / len(bestActions)
        for a in legalActions: dist[a] += ( 1-bestProb ) / len(legalActions)
        dist.normalize()
        return dist
