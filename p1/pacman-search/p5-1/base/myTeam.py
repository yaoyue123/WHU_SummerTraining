# myTeam.py
# ---------
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


from captureAgents import CaptureAgent, RandomAgent
import random, time, util
from game import Directions
import game
import subprocess
from subprocess import PIPE

#################
# Team creation #
#################

def createTeam(firstIndex, secondIndex, isRed,
               first = 'DummyAgent', second = 'DummyAgent'):
  """
  This function should return a list of two agents that will form the
  team, initialized using firstIndex and secondIndex as their agent
  index numbers.  isRed is True if the red team is being created, and
  will be False if the blue team is being created.

  As a potentially helpful development aid, this function can take
  additional string-valued keyword arguments ("first" and "second" are
  such arguments in the case of this function), which will come from
  the --redOpts and --blueOpts command-line arguments to capture.py.
  For the nightly contest, however, your team will be created without
  any extra arguments, so you should make sure that the default
  behavior is what you want for the nightly contest.
  """

  # The following line is an example only; feel free to change it.
  #return [eval(first)(firstIndex)]
  return [eval(first)(firstIndex), eval('RandomAgent')(secondIndex)]

##########
# Agents #
##########

class DummyAgent(CaptureAgent):
  """
  A Dummy agent to serve as an example of the necessary agent structure.
  You should look at baselineTeam.py for more details about how to
  create an agent as this is the bare minimum.
  """

  def registerInitialState(self, gameState):
    """
    This method handles the initial setup of the
    agent to populate useful fields (such as what team
    we're on).

    A distanceCalculator instance caches the maze distances
    between each pair of positions, so your agents can use:
    self.distancer.getDistance(p1, p2)

    IMPORTANT: This method may run for at most 15 seconds.
    """

    '''
    Make sure you do not delete the following line. If you would like to
    use Manhattan distances instead of maze distances in order to save
    on initialization time, please take a look at
    CaptureAgent.registerInitialState in captureAgents.py.
    '''
    CaptureAgent.registerInitialState(self, gameState)

    '''
    Your initialization code goes here, if you need any.
    '''


  def chooseAction(self, gameState):
    """
    Picks among actions randomly.
    """
    actions = gameState.getLegalActions(self.index)

    '''
    You should change this in your own agent.
    '''
    return self.run(gameState, '../build/pacman.out')

  def run(self, gameState, path):
      walls = gameState.getWalls()
      #ghosts = gameState.getGhostStates()

      m, n = len(walls.data), len(walls.data[0])
      x1, y1 = gameState.getAgentPosition(0)
      x1, y1 = n - y1 - 1, x1
      x2, y2 = gameState.getAgentPosition(1)
      x2, y2 = n - y2 - 1, x2
      data = '%i %i\n%s\n%i %i\n%i %i\n%s\n%i\n2\n' % (n, m, walls, x1, y1, x2, y2, gameState.data.food, self.index)
      for i in range(2, 4):
          x3, y3 = gameState.getAgentPosition(i)
          x3, y3 = n - y3 - 1, x3
          data += '%i %i\n' % (x3, y3)

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

