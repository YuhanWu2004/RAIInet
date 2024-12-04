# RAIInet

This is a game implemented using C++. 
RAIInet is a game played between two opposing players, who take on the role of computer hackers. 
Each player controls eight pieces, called links. There are two different kinds of links: viruses and data. Each player has two goals:
• Download four data.
• Make their opponent download four viruses.
Upon achieving either goal, the player wins the game.
A game of RAIInet consists of an 8 × 8 board on which players initially place links face-down. In this way, only the player
who placed the link knows whether it is data or a virus.
Play then proceeds in turns. On each player’s turn, a player may use a single ability, and then must move one of their links
in any cardinal direction.

# Display
The text display and the graphical display of this game are both enabled

# Link:
There are two kinds of links: data, and viruses. If at any point a player has downloaded four data, they win the game.
Conversely, if they have downloaded four viruses, they lose the game. In addition to being viruses or data, links have a
strength between 1 and 4, with 1 being the weakest and 4 being the strongest. Initially, players are given viruses and data of
each possible strength, for a total of 8 links.

# Movement, Battle, and Capture:
Each turn a player must move a single link they control one space in a cardinal direction. (There is a “global compass”, so
north is the same direction for both players.) This movement is subject to a few conditions:
• One cannot move a link on top of another link one controls (but can on top of an opponent’s link; see below).
• One cannot move a link on top of one’s own server ports.
• One cannot move a link off the edge of the board, except off the edge upon which one’s opponent’s links started i.e.
either the top or the bottom edge, respectively. When one moves a link off the edge in this way, one downloads that
link.
• If a link moves into one’s opponent’s server port, it is downloaded by one’s opponent.
• When a link is moved on top of a link controlled by one’s opponent, both links are revealed to all players and they battle;
the winner is the player whose link had higher strength. In the event of a tie, the initiating player wins the battle. After
the battle, the winner downloads the link of the loser.
After moving one link, one’s turn ends. This is the only way a turn can be ended. Downloading a link must update the
appropriate counters. It is up to you as to whether or not the link’s value is revealed.

# Abilities:
In addition to the basic movements, each player has a set of five ability cards available to them at the start of the game. Each
card can only be used once per game; however, players select which cards they wish to use, and can take up to 2 of each kind.
For example, player 1 may decide to start the game with two copies of the card Firewall, two copies of the card Download,
and one copy of the card Polarize. In this case, player 1 would be able to download two of player 2’s links, by using both their
download cards. The five abilities your game must support are as follows:
1. Link boost:
    Link boostmodifies a link you control by making it move one additional square in each direction when it moves. This allows
the link to “jump over” obstacles. A link with a link boost equipped may be unable to reach the opponent server port.
This effect remains active until the link is downloaded.
2. Firewall:
    Firewall is played targeting any empty square on the board other than the server ports. When passing through this square,
opponent links are revealed and, if they are viruses, immediately downloaded by their owner. A square with a firewall
with it is usually printed to the display with an “m” for a firewall by player 1 and a “w” for a firewall by player 2. If
a link is placed on a firewall, print the link rather than the firewall. Links owned by the player who placed firewall are
unaffected by this ability. If an opponent attempts to battle a player’s link which is stationed on the player’s firewall:
the firewall effect applies prior to the battle taking place.
3. Download:
    Download immediately downloads an opponent’s targeted link. It does not need to be revealed.
4. Polarize:
    Polarize changes a targeted data to a virus of the same strength, or vice versa.
5. Scan
    Scan reveals the type and strength of any targeted link on the field. It does not reveal the player’s own links.
6. Brutal:
    This ability can be used on user’s own links to make sure the link wins any battle.
7. Protected:
    This ability can be use on user’s own links to protect it from being downloaded
directly by the opponent calling download ability on it. Note this doesn’t change the link’s
behavior in a battle.
8. Trade:
    Player can use this ability by calling “ability 8 [link name]”, it can only be called on
player’s own links and this will trade players link with the opponent’s corresponding link (a-
A, B-b, etc.). A link that is already downloaded cannot be traded! (applies both to the player
and the opponent, that is, if the corresponding link belonging to the opponent is
downloaded, this ability fails as well). After the trading, the link name doesn’t change, but
the value and the type will change to the opponent’s link, same applies to the opponent’s
link.

# Winning and Losing
When a player has downloaded four data, regardless of their strength or who they belonged to originally, the player wins the
game. Conversely, if whenever a player has downloaded four viruses, they immediately lose the game. Your program need not
have a game-over screen, but it must be clear that the program stopped because a player won the game, and it must indicate
which player won.

# Interactions
You interact with the system by issuing text-based commands. The following commands are to be supported:
• move a <dir> moves the link a (where this can be any link one controls) in the direction dir, which can be any of
up, down, left, right. The link a can be any value from a-g (or A-G for player 2).
• abilities displays the ability cards one has, together with an ID (from 1-5) and some indication if the ability card
has been used or not.
• ability <N> uses the ability card with ID N. Some ability cards will require additional information, such as a target
for Link Boost, or a square of the board for Firewall. Your program must support giving links as targets using the
alphabetical code shown in the display section; so if ability 1 is Link Boost, ability 1 b attaches a Link
Boost to the link b. Squares, such as for Firewall, must be specified by row and then column, where the top left corner
is (0, 0). For example, to place a firewall directly below one of player 1’s server ports, one would use ability 1 1
3 or ability 1 1 4, assuming that ability 1 is Firewall.
• board displays the board in the format shown in the Display section.
• sequence <file> Executes the sequence of commands found in file, where commands are given as described in
this section. This is to facilitate the construction of test cases.
• quit or end-of-file (Ctrl-d) exits the game.

# Setup
• -ability1 <order> specifies the abilities for player 1 (this is a list of the 5 abilities player 1 will use). If not
specified, use the default set of abilities (Link boost, Firewall, Download, Scan, Polarize in that order). The abilities are
given by a string consisting of the first letter of each ability. For example, the default order is -ability1 LFDSP.
Ensure that when you add new abilities, they start with different letters.
• -ability2 <order> is as above but for the second player.
• -link1 <placement-file>. The contents of <placement-file> should list what each link should be for
player 1. The first token of <placement-file> specifies what link a is, the second, b, and so on and so forth. For
example, the example board in the display section can be made with passing -link1 a file containing “V1 D4 V3
V2 D3 V4 D2 D1”.
If -link1 is not passed to your program, then you should randomize the order of the links that player 1 receives.
• -link2 <order> is as above but for the second player.
• -graphics should enable your graphical interface.






