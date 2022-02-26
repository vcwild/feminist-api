#include "mongoose.h"

#define MAX_LENGTH 1024

// TODO: develop a proper database and parsing
// for this implementation that would solve both front-end and back-end.

static int gen_random_pos(const char message_pairs[][3][MAX_LENGTH]) {
  int pairs_iter = 0;
  while(**message_pairs[pairs_iter])
    pairs_iter++;
  return rand() % (pairs_iter - 2);
}

void dispatch_quote(struct mg_connection *c) {
  char *json_template = "{\"message\": \"%s\", \"author\": \"%s\"}\n";
  const char message_pairs[][3][MAX_LENGTH] = {
    {"It took me quite a long time to develop a voice, and now that I have it, I am not going to be silent.","Madeleine Albright"},
    {"I raise up my voice—not so that I can shout, but so that those without a voice can be heard. We cannot all succeed when half of us are held back.", "Malala Yousafzai"},
    {"A woman with a voice is, by definition, a strong woman", "Melinda Gates"},
    {"I am not free while any woman is unfree, even when her shackles are very different from my own.", "Audre Lorde"},
    {"The more I have spoken about feminism the more I have realized that fighting for women's rights has too often become synonymous with man-hating. If there is one thing I know for certain, it is that this has to stop","Emma Watson"},
    {"Women must learn to play the game as men do.","Eleanor Roosevelt"},
    {"No woman should be told she can't make decisions about her own body. When women's rights are under attack, we fight back.","Kamala Harris"},
    {"I feel now that the time is come when even a woman or a child who can speak a word for freedom and humanity is bound to speak.","Harriet Beecher Stowe"},
    {"In the future, there will be no female leaders. There will just be leaders.","Sheryl Sandberg"},
    {"Women's freedom is the sign of social freedom.","Rosa Luxemburg"},
    {"Women have discovered that they cannot rely on men's chivalry to give them justice.","Helen Keller"},
    {"Another world is not only possible, she is on her way. On a quiet day, I can hear her breathing.","Arundhati Roy"},
    {"More and more women are realizing that only collective strength and action will allow us to be free to fight for the kind of society that meets basic human needs.","Roxanne Dunbar"},
    {"A revolutionary woman can't have no reactionary man.","Assata Shakur"},
    {"There is no gate, no lock, no bolt that you can set upon the freedom of my mind.","Virginia Woolf"},
    {"I am a woman and a warrior. If you think I can't be both, you've been lied to.", "Jennifer Zeynab Joukhadar"}
  };

  int rand_pos = gen_random_pos(message_pairs);
  mg_http_reply(
    c, 200, "Content-type: application/json\r\n",
    json_template,
    message_pairs[rand_pos][0], message_pairs[rand_pos][1]
  );
}