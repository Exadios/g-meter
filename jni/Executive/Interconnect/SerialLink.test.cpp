/*
Copyright_License {

  G-Meter INU.
  Copyright (C) 2013-2015 Peter F Bradshaw
  A detailed list of copyright holders can be found in the file "AUTHORS".

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
}
*/

#include "SerialLink.test.hpp"
#include <stdlib.h>
#include <fcntl.h>
#include <linux/limits.h>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/utility.hpp>
#include <boost/system/error_code.hpp>
#include <iostream>
#include <fstream>

/**
 *
 */
class Pts
  {
public:
  /**
   * Ctor.
   */
  Pts();

  /**
   * Dtor.
   */
  ~Pts();

  /**
   * Test whether the pty / tty pair are OK.
   * @return If OK then true.
   */
  bool Go() const;

  /**
   * Give the pty file descritor.
   * @return The open pty descriptor.
   */
  int PtyFd() const;

  /**
   * Give the tty name.
   * @return The fully qualified tty name for use as a tty.
   */
  const char *Tty() const;

private:
  bool go;
  int fd;
  char tty[PATH_MAX + 1];
  char pty[PATH_MAX + 1];
  };

//------------------------------------------------------------------------------
Pts::Pts()
  : go(false),
    fd(-1)
  {
  this->fd = posix_openpt(O_RDWR | O_NOCTTY);
  if (this->fd == -1)
    {
    std::cerr << "Pts could not open master: "
              << strerror(errno) << std::endl;
    this->go = false;
    return;
    }

  if (ptsname_r(this->fd, this->tty, sizeof(this->tty) / sizeof(char) - 1) != 0)
    {
    std::cerr << "CreatePty could not get tty name: "
              << strerror(errno) << std::endl;
    this->go = false;
    return;
    }

  if (grantpt(this->fd) == -1)
    {
    std::cerr << "CreatePty could not set tty owner: "
              << strerror(errno) << std::endl;
    this->go = false;
    return;
    }

  if (unlockpt(this->fd) == -1)
    {
    std::cerr << "CreatePty could not unlock pty / tty: "
              << strerror(errno) << std::endl;
    this->go = false;
    return;
    }

  this->go = true;
  }

//------------------------------------------------------------------------------
bool
Pts::Go() const
  {
  return this->go;
  }

//------------------------------------------------------------------------------
int
Pts::PtyFd() const
  {
  return this->fd;
  }

//------------------------------------------------------------------------------
const char *
Pts::Tty() const
  {
  return this->tty;
  }

/**
 *
 */
class PseudoSource : public boost::noncopyable
  {
public:
  /**
   * Ctor.
   */
  PseudoSource(std::istream& in,
               std::ostream& out,
               const std::string dev,
               boost::asio::io_service& io);

  /**
   * Dtor.
   */
  ~PseudoSource();

  /**
   * Run the pty loop.
   */
  void Run();

  /**
   * Is OK?
   * @return Of go then true.
   */
  bool Go() const;

private:
  void InitiateRead();

  void InitiateWrite();

  void HandleRead(const boost::system::error_code ec, std::size_t n);

  void HandleWrite(const boost::system::error_code ec);

  std::istream& in;
  std::ostream& out;
  boost::asio::io_service& io;
  boost::asio::serial_port serial_port;
  boost::asio::streambuf b;
  };

//------------------------------------------------------------------------------
PseudoSource::PseudoSource(std::istream& in,
                           std::ostream& out,
                           const std::string dev,
                           boost::asio::io_service& io)
  : in(in),
    out(out),
    io(io),
    serial_port(io)
  {
  this->serial_port.open(dev);
  }

//------------------------------------------------------------------------------
PseudoSource::~PseudoSource()
  {
  }

//------------------------------------------------------------------------------
void
PseudoSource::Run()
  {
  this->InitiateRead();
  this->InitiateWrite();

  io.run();
  }

//------------------------------------------------------------------------------
bool
PseudoSource::Go() const
  {
  return ((this->in.good() == true) &&
          (this->out.good()== true) &&
          (this->serial_port.is_open() == true));
  }

//------------------------------------------------------------------------------
void
PseudoSource::InitiateRead()
  {
  boost::asio::async_read_until(this->serial_port,
                                this->b,
                                std::string("\r\n"),
                                boost::bind(&PseudoSource::HandleRead,
                                            this,
                                            boost::asio::placeholders::error,
                                            boost::asio::placeholders::bytes_transferred)
                               );
  }

//------------------------------------------------------------------------------
void
PseudoSource::InitiateWrite()
  {
  std::string record;
  std::getline(this->in, record);
  boost::asio::async_write(this->serial_port,
                           boost::asio::buffer(record, record.size()),
                           boost::bind(&PseudoSource::HandleWrite,
                                       this,
                                       boost::asio::placeholders::error)
                          );
  }

//------------------------------------------------------------------------------
void
PseudoSource::HandleRead(const boost::system::error_code ec, std::size_t n)
  {
  this->b.commit(n);
  std::istream input(&this->b);
  std::string record;
  std::getline(input, record);
  this->out << record;
  this->b.consume(n);
  }

//------------------------------------------------------------------------------
void
PseudoSource::HandleWrite(const boost::system::error_code ec)
  {
  if (!ec)
    {
    this->InitiateWrite();
    }
  }

/**
 *
 */
class Args
  {
public:
  /**
   * Ctor.
   */
  Args(int argc, const char *argv[]);
   
  /**
   * Dtor.
   */
  ~Args();

  /**
   * Give the tty used by the code under test.
   */
  const std::string Ttys() const;

  /**
   * Give the tty used by the tester.
   */
  const std::string Ttym() const;

  /**
   * Give the in stream.
   */
  const std::ifstream& In() const;

  /**
   * Give the out stream.
   */
  const std::ofstream& Out() const;

  /**
   *
   */
  bool Go() const;

private:
  /**
   *
   */
  bool ArgTuple(int i, 
                int argc,
                const char *argv[],
                const std::string sw,
                std::string *ret);

  bool go;
  std::string ttys;
  std::string ttym;
  std::string inf;
  std::string outf;
  std::ifstream in;
  std::ofstream out;
  };

//------------------------------------------------------------------------------
Args::Args(int argc, const char *argv[])
  : go(true)
  {
  for (int i = 0; i < argc; i++)
    {
    bool g0, g1, g2, g3;

    g0 = ArgTuple(i, argc, argv, "-s", &this->ttys);
    g1 = ArgTuple(i, argc, argv, "-m", &this->ttym);
    g2 = ArgTuple(i, argc, argv, "-i", &this->inf);
    g3 = ArgTuple(i, argc, argv, "-o", &this->outf);
    this->go = this->go && (g0 || g1 || g2 || g3);
    }

  if (this->go == true)
    {
    this->in.open(this->inf);
    this->go = this->in.good();
    }
  if (this->go == true)
    {
    this->out.open(this->outf);
    this->go = this->out.good();
    }
  }

//------------------------------------------------------------------------------
Args::~Args()
  {
  }

//------------------------------------------------------------------------------
const std::string
Args::Ttys() const
  {
  return this->ttys;
  }

//------------------------------------------------------------------------------
const std::string
Args::Ttym() const
  {
  return this->ttym;
  }

//------------------------------------------------------------------------------
const std::ifstream&
Args::In() const
  {
  return this->in;
  }

//------------------------------------------------------------------------------
const std::ofstream&
Args::Out() const
  {
  return this->out;
  }

//------------------------------------------------------------------------------
bool
Args::Go() const
  {
  return this->go;
  }

//------------------------------------------------------------------------------
bool
Args::ArgTuple(int i,
               int argc,
               const char *argv[],
               const std::string sw,
               std::string *ret)
  {
  if (i >= (argc - 2))
    return false;
  if (argv[i + 1][0] == '-')
    return false;   // Probably not right.
  if (argv[i] == sw)
    {
    *ret = argv[i + 1];
    return true;
    }
  else
    return false;
  }
  
void TestMain(const char *tty);

//------------------------------------------------------------------------------
void
TestMain(const char *tty)
  {
  boost::asio::io_service io;
  SerialLink ut(io, tty);
  io.run();
  }

//------------------------------------------------------------------------------
int
main(int argc, const char *argv[])
  {
  Args args(argc, argv);

  if (args.Go() == true)
    {
    boost::thread test(TestMain, args.Ttys().c_str());
    test.join();
    }

  return 0;
  }
