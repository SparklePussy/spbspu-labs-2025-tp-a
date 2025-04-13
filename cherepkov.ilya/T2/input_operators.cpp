#include "input_operators.hpp"


std::istream& cherepkov::operator>>(std::istream& in, DelimiterIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char c = '0';
  in >> c;
  c = std::tolower(c);

  if (in && (c != dest.exp))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& cherepkov::operator>>(std::istream& in, UllLitValue&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return in >> dest.ref >> DelimiterIO{ 'u' } >> DelimiterIO{ 'l' } >> DelimiterIO{ 'l' } >> DelimiterIO{ ':' };
}

std::istream& cherepkov::operator>>(std::istream& in, UllBinValue&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char c = 0;
  unsigned long long number = 0;
  in >> DelimiterIO { '0' } >> DelimiterIO { 'b' };
  while (in >> c)
  {
    if (c == '1' || c == '0')
    {
      number = (number << 1) + (c - '0');
    }
    else
    {
      break;
    }
  }
  if (c == ':')
  {
    dest.ref = number;
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& cherepkov::operator>>(std::istream& in, StringValue&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
  in >> DelimiterIO{ ':' };

  return in;
}

std::string cherepkov::ULLtoBinary(unsigned long long val)
{
  if (val == 0)
  {
    return "0";
  }
  std::string bin;
  while (val > 0)
  {
    bin.insert(0, std::to_string(val % 2));
    val /= 2;
  }
  return bin;
}
